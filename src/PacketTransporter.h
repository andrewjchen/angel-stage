#ifndef PACKET_TRANSPORTER_H
#define PACKET_TRANSPORTER_H
#include <deque>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "packet.h"

class PacketTransporter
{
public:
	PacketTransporter(TCPsocket _sock);
	void processNetworkRead();
	void processNetworkWrite();
	Packet *getRXPacket();
	void addTXPacket(Packet *pkt);
	void close();
	static void peer_thread_read(PacketTransporter *nm);
	static void peer_thread_write(PacketTransporter *nm);
	
	boost::thread *read_thread;
	boost::thread *write_thread;

private:
	TCPsocket sock;
	std::deque<Packet *> rx_queue;
	std::deque<Packet *> tx_queue;
	boost::mutex rx_mutex;
	boost::mutex tx_mutex;
	bool closed;
};

#endif
