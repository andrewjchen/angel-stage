#ifndef NETCONNECT_H
#define NETCONNECT_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "network_manager.h"

class NetworkConnector
{
public:
	NetworkConnector(const char * server, uint16_t port);
	~NetworkConnector();
	void connect();
	NetworkManager* network_manager;

private:
	TCPsocket clientSock;
};

#endif
