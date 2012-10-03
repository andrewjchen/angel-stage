#ifndef NETCONNECT_H
#define NETCONNECT_H
#include <vector>
#include <list>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "Packet.hxx"

class NetworkConnecter {
public:
    NetworkConnecter(const char *server, uint16_t port);
    virtual ~NetworkConnecter();

    void start();
    void disconnect();
    bool isConnected();

    void send_packet(Packet *p);
    void send_packet(std::list<Packet *> ps);
    std::list<Packet *> *get_packet(int n = 1);

private:
    bool valid;
    bool running;

    uint8_t *crunchIntoBuffer(std::list<Packet *> ps, int *outsize);

    int sockfd;

    void readthread();
    boost::thread *readThread;
    boost::mutex queue_mutex;
    std::deque<Packet *> rx_queue;
};

#endif
