#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "PacketTransporter.hxx"

/**
 * ClientAccepter runs a thread polling for new client sockets.
 * When one is found, it constructs a PacketTransporter and launches
 * the PacketTransporter read/write threads
 * 
 * Accessing packetTransporters requires that the packetTransport 
 * mutex be locked. 
 */
class ClientAccepter
{
public:
	ClientAccepter(uint16_t port);
	~ClientAccepter();

	void start();

	boost::mutex nm_mutex;

	//TODO map int->PacketTransporter*?
	std::vector<PacketTransporter*> packetTransporters;

private:
	void tick();
	void listen();
	TCPsocket listenSock;
	boost::thread* listenThread;
};

#endif
