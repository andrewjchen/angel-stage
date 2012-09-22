#ifndef NETCONNECT_H
#define NETCONNECT_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "PacketTransporter.hxx"
#include "Packet.hxx"

class NetworkConnecter
{
public:
	NetworkConnecter(const char * server, uint16_t port);
	virtual ~NetworkConnecter();
	void connect();
	void disconnect();
	bool isConnected();

	void sendPacket(Packet* p);
	Packet* getPacket();

private:
	PacketTransporter* packetTransport; /* deleted in disconnect() */
	TCPsocket clientSock;
};

#endif
