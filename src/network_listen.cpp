#include <iostream>
#include "network_listen.h"

NetworkListener::NetworkListener(uint16_t port)
{
	IPaddress ip;
	
	if(SDLNet_ResolveHost(&ip, NULL, port) != 0)
		throw "SDLNet_ResolveHost error";
	
	listenSock = SDLNet_TCP_Open(&ip);
	if(listenSock == NULL)
		throw "SDLNet_TCP_Open error";
}

NetworkListener::~NetworkListener()
{
	if(listenSock)
		SDLNet_TCP_Close(listenSock);
}

void NetworkListener::process()
{
	if(listenSock == NULL)
		throw "listenSock is null!";
	TCPsocket clientSock;
	while((clientSock = SDLNet_TCP_Accept(listenSock)) != NULL)
	{
		std::cout << "asdf\n";
		SDLNet_TCP_Close(clientSock);
	}
}
