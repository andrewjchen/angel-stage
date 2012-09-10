#ifndef NETLISTEN_H
#define NETLISTEN_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "network_manager.h"

class NetworkListener
{
public:
	NetworkListener(uint16_t port);
	~NetworkListener();
	void process();
	boost::mutex nm_mutex;
	std::vector<NetworkManager*> network_managers;

private:
	TCPsocket listenSock;
};

#endif
