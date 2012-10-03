#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H
#include <map>
#include <list>
#include <deque>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include <boost/function.hpp>
#include "SDL/SDL_net.h"
#include "Packet.hxx"

#define CLIENT_ID_EVERYBODY 0

/**
 * ClientsConnection runs a thread polling for new client sockets.
 * When one is found, it constructs a PacketTransporter and launches
 * the PacketTransporter read/write threads
 *
 * Accessing packetTransporters requires that the packetTranspor t
 * mutex be locked.
 */
class ClientsConnection {
public:
    ClientsConnection(uint16_t port, boost::function<void (uint64_t, int)> _onLoginCallback);
    ~ClientsConnection();

    void start();
    void stop();

    void send_packet(Packet *p, uint64_t client);
    void send_packet(Packet *p);
    void send_packet(std::list<Packet *> ps, uint64_t client);
    void send_packet(std::list<Packet *> ps);
    std::list<Packet *> *get_packets(int n = 1);
    void closeClient(uint64_t client);

    friend class Server;

private:
    bool valid;
    bool running;

    void listenthread();
    void readthread();

    static uint8_t *crunchIntoBuffer(std::list<Packet *> ps, int *outsize);

    boost::thread *listenThread;
    boost::thread *readThread;
    boost::mutex queue_mutex;
    std::deque<Packet *> rx_queue;

    int listenfd;
    std::map<uint64_t,int> clientfds;
    std::map<int,uint64_t> fd_to_client;
    boost::mutex clientfd_mutex;

    boost::function<void (uint64_t, int)> onLoginCallback;
};

#endif
