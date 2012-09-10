#ifndef NETCONNECT_H
#define NETCONNECT_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "PacketTransporter.hxx"

class NetworkConnecter
{
public:
	NetworkConnecter(const char * server, uint16_t port);
	~NetworkConnecter();
	void connect();
	PacketTransporter* network_manager;

private:
	TCPsocket clientSock;
};

#endif
