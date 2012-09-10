#include <iostream>
#include <boost/thread/thread.hpp>
#include <stdint.h>

#include "network_manager.h"

NetworkManager::NetworkManager(TCPsocket _sock)
{
	sock = _sock;
}

void NetworkManager::peer_thread(NetworkManager *nm)
{
	while(1)
	{
		//std::cout << "peer_thread\n";
		nm->processNetwork();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

void NetworkManager::processNetwork()
{
	uint8_t type;
	uint32_t len;
	
	std::cout << "processNetwork\n";
	
	SDLNet_TCP_Recv(sock, &type, 1);
	SDLNet_TCP_Recv(sock, &len, 4);
	
	std::cout << type << len;
}
