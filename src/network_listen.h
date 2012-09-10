#ifndef NETLISTEN_H
#define NETLISTEN_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"

class NetworkListener
{
public:
	NetworkListener(uint16_t port);
	~NetworkListener();
	void process();

private:
	TCPsocket listenSock;
	std::vector<boost::thread*> peer_threads;
};

#endif
