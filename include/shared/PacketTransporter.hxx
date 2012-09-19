#ifndef PACKET_TRANSPORTER_H
#define PACKET_TRANSPORTER_H
#include <deque>
#include <boost/thread/thread.hpp>
#include "SDL/SDL_net.h"
#include "Packet.hxx"

/**
 * PacketTransporter sends and receives packets through a socket connection.
 * It runs the threads to do this IO thread safe, stores packets
 * for sending and receiving in queues
 * 
 * MUST BE ALLOCATED WITH new
 */
//TODO queue overflow?
class PacketTransporter
{
public:
	PacketTransporter(TCPsocket _sock);
	virtual ~PacketTransporter() {}; // Have this or use a struct instead.

	//called each read/write loop
	void processNetworkRead();
	void processNetworkWrite();

	//get the latest rx packet
	Packet *getRXPacket();
	//adds a packet to be sent
	void addTXPacket(Packet *pkt);
	void close();

	//Starts read/write threads.
	//TODO make not static
	static void peer_thread_read(PacketTransporter *nm);
	static void peer_thread_write(PacketTransporter *nm);

	boost::thread *read_thread;
	boost::thread *write_thread;
	
	TCPsocket sock;
	
	uint64_t peer_ip;

private:
	std::deque<Packet *> rx_queue;
	std::deque<Packet *> tx_queue;
	boost::mutex rx_mutex;
	boost::mutex tx_mutex;
	bool closed_read;
	bool closed_write;
};

#endif
