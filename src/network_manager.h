#ifndef NETMANAGER_H
#define NETMANAGER_H
#include "SDL/SDL_net.h"

class NetworkManager
{
public:
	NetworkManager(TCPsocket _sock);
	void processNetwork();
	void *getRXPacket();
	void addTXPacket();
	void close();
	static void peer_thread(NetworkManager *nm);

private:
	TCPsocket sock;
};

#endif
