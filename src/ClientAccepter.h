#ifndef CLIENT_ACCEPTER_H
#define CLIENT_ACCEPTER_H
#include <vector>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "PacketTransporter.h"

class ClientAccepter
{
public:
	ClientAccepter(uint16_t port);
	~ClientAccepter();
	void process();
	boost::mutex nm_mutex;
	std::vector<PacketTransporter*> PacketTransporters;

private:
	TCPsocket listenSock;
};

#endif
