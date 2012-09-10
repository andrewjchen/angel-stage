#ifndef NETLISTEN_H
#define NETLISTEN_H
#include <stdint.h>
#include "SDL/SDL_net.h"

class NetworkListener
{
public:
	NetworkListener(uint16_t port);
	~NetworkListener();
	void process();

private:
	TCPsocket listenSock;
};

#endif
