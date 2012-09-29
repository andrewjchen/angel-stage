#ifndef NETCONNECT_H
#define NETCONNECT_H
#include <vector>
#include <list>
#include <memory>
#include <stdint.h>
#include <boost/thread/thread.hpp>
#include "Packet.hxx"

class NetworkConnecter
{
public:
	NetworkConnecter(const char * server, uint16_t port);
	virtual ~NetworkConnecter();
	
	void start();
	void disconnect();
	bool isConnected();

	void sendPacket(Packet* p);
	std::list<Packet*> getPacket(int n = 1);

private:
	bool valid;
	bool running;
	
	int sockfd;
	
	void readthread();
	boost::thread *readThread;
	boost::mutex queue_mutex;
	std::deque<Packet *> rx_queue;
};

#endif
