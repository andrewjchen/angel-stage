#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H
#include <map>
#include <list>
#include <deque>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "Packet.hxx"

#define CLIENT_ID_EVERYBODY 0

/**
 * ClientsConnection runs a thread polling for new client sockets.
 * When one is found, it constructs a PacketTransporter and launches
 * the PacketTransporter read/write threads
 * 
 * Accessing packetTransporters requires that the packetTransport 
 * mutex be locked. 
 */
class ClientsConnection
{
public:
	ClientsConnection(uint16_t port);
	~ClientsConnection();

	void start(); 
	void stop();

	void sendPacket(Packet *p, uint64_t client);
	void sendPacket(Packet *p);
	std::list<Packet*> getPackets(int n = 1);
	void closeClient(uint64_t client);

private:
	bool valid;
	bool running;
	
	void listenthread();
	void readthread();
	
	void sendOnLoginData(uint64_t client, int fd);
	
	boost::thread *listenThread;
	boost::thread *readThread;
	boost::mutex queue_mutex;
	std::deque<Packet *> rx_queue;
	
	int listenfd;
	std::map<uint64_t,int> clientfds;
	std::map<int,uint64_t> fd_to_client;
	boost::mutex clientfd_mutex;
};

#endif
