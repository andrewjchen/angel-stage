#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "PacketTransporter.hxx"
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

	//starts listening for 
	void start(); 
	void stop();

	void sendPacket(Packet *p, uint64_t client);
	void getPackets();

	boost::mutex nm_mutex;

	//TODO map int->PacketTransporter*?
	std::vector<PacketTransporter*> packetTransporters;

private:
	bool running;
	void tick(); //called by listen thread
	void listen(); //called by start()
	TCPsocket listenSock;
	boost::thread* listenThread;
};

#endif
