#ifndef NETMANAGER_H
#define NETMANAGER_H
#include <deque>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "packet.h"

class NetworkManager
{
public:
	NetworkManager(TCPsocket _sock);
	void processNetworkRead();
	void processNetworkWrite();
	Packet *getRXPacket();
	void addTXPacket(Packet *pkt);
	void close();
	static void peer_thread_read(NetworkManager *nm);
	static void peer_thread_write(NetworkManager *nm);
	
	boost::thread *read_thread;
	boost::thread *write_thread;
	
	TCPsocket sock;

private:
	std::deque<Packet *> rx_queue;
	std::deque<Packet *> tx_queue;
	boost::mutex rx_mutex;
	boost::mutex tx_mutex;
	bool closed_read;
	bool closed_write;
};

#endif
