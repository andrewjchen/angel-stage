#include <iostream>
#include <poll.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "NetworkConnecter.hxx"

NetworkConnecter::NetworkConnecter(const char *server, uint16_t port) {
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(struct sockaddr_in));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if(inet_pton(AF_INET, server, &sa.sin_addr.s_addr) != 1)
        throw "inet_pton error";

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
        throw "socket error";

    if(connect(sockfd, (struct sockaddr *)&sa, sizeof(sa)) == -1)
        throw "connect error";

    valid = true;
    running = false;
}

NetworkConnecter::~NetworkConnecter() {
    if (running) {
        disconnect();
    }
}

void NetworkConnecter::start() {
    if(running)
        throw "Already running!";
    if(!valid)
        throw "Stopped! (and therefore invalid)";

    running = true;
    readThread = new boost::thread(boost::bind(&NetworkConnecter::readthread, this));
}

void NetworkConnecter::disconnect() {
    valid = false;
    running = false;

    readThread->join();
    delete readThread;
    readThread = NULL;

    if(sockfd > 0) {
        close(sockfd);
        sockfd = -1;
    }
}

void NetworkConnecter::readthread() {
    while(running) {
        struct pollfd pfd[1];
        pfd[0].fd = sockfd;
        pfd[0].events = POLLIN;
        pfd[0].revents = 0;

        int pollres = poll(pfd, 1, 5000);

        if(pollres == -1) {
            valid = false;
            throw "poll error";
        }

        if(pollres == 1) {
            if((pfd[0].revents & POLLERR) || (pfd[0].revents & POLLNVAL)) {
                std::cout << "Error poll from server\n";
                valid = false;
                running = false;
                close(sockfd);
                return;
            }

            if(pfd[0].revents & POLLIN) {
                Packet *p = Packet::readByType(pfd[0].fd);
                if(p) {
                    queue_mutex.lock();
                    rx_queue.push_back(p);
                    queue_mutex.unlock();
                }
            }
        }
    }
}

bool NetworkConnecter::isConnected() {
    return running;
}

uint8_t *NetworkConnecter::crunchIntoBuffer(std::list<Packet *> ps, int *outsize) {
    int size = 0;
    for(std::list<Packet *> ::iterator it = ps.begin(); it != ps.end(); it++)
        size += (*it)->estimateSize();

    uint8_t *buf = new uint8_t[size];
    int i = 0;
    for(std::list<Packet *> ::iterator it = ps.begin(); it != ps.end(); it++)
        i += (*it)->writeToBuf(buf + i);

    *outsize = i;
    return buf;
}

void NetworkConnecter::send_packet(std::list<Packet *> ps) {
    int size;
    uint8_t *b = crunchIntoBuffer(ps, &size);
    write(sockfd, b, size);
    delete[] b;
}

void NetworkConnecter::send_packet(Packet *p) {
    std::list<Packet *> ps;
    ps.push_back(p);
    send_packet(ps);
}

std::list<Packet *> *NetworkConnecter::get_packet(int n) {
    std::list<Packet *> *retu = new std::list<Packet *>;

    queue_mutex.lock();
    for(int i = 0; i < n; i++) {
        if(rx_queue.size() == 0) break;
        retu->push_back(rx_queue.front());
        rx_queue.pop_front();
    }
    queue_mutex.unlock();

    return retu;
}
