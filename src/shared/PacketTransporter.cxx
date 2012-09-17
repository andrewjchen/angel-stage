#include <iostream>
#include <boost/thread/thread.hpp>
#include <stdint.h>

#include "PacketTransporter.hxx"
#include "Packet.hxx"

PacketTransporter::PacketTransporter(TCPsocket _sock)
{
	sock = _sock;
	closed_read = closed_write = false;
}

void PacketTransporter::peer_thread_read(PacketTransporter *nm)
{
	while(1)
	{
		//std::cout << "peer_thread\n";
		nm->processNetworkRead();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		if(nm->closed_read)
			break;
	}
}

void PacketTransporter::processNetworkRead()
{
	uint8_t type;
	
	std::cout << "processNetworkRead\n";
	
	if(SDLNet_TCP_Recv(sock, &type, 1) <= 0)
	{
		//error
		//hack
		Packet *p = new PacketDisconnect(PACKET_DISCONNECT);
		rx_mutex.lock();
			rx_queue.push_back(p);
		rx_mutex.unlock();
		return;
	}
	
	//std::cout << type << len;
	Packet *p = Packet::readByType(sock, type);
	
	rx_mutex.lock();
		rx_queue.push_back(p);
	rx_mutex.unlock();
}

Packet *PacketTransporter::getRXPacket()
{
	Packet *p = 0;
	rx_mutex.lock();
		if(rx_queue.size() != 0)
		{
			p = rx_queue.front();
			rx_queue.pop_front();
		}
	rx_mutex.unlock();
	
	return p;
}

void PacketTransporter::peer_thread_write(PacketTransporter *nm)
{
	while(1)
	{
		//std::cout << "peer_thread\n";
		nm->processNetworkWrite();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		if(nm->closed_write)
			break;
	}
}

void PacketTransporter::processNetworkWrite()
{
	//std::cout << "processNetworkWrite\n";
	
	tx_mutex.lock();
		while(tx_queue.size() > 0)
		{
			Packet *pout = tx_queue.front();
			tx_queue.pop_front();
			std::cout << "processNetworkWrite" << pout->type << "\n";
			pout->write(sock);
			delete pout;
		}
	tx_mutex.unlock();
}

void PacketTransporter::addTXPacket(Packet *pkt)
{
	tx_mutex.lock();
		tx_queue.push_back(pkt);
	tx_mutex.unlock();
}

void PacketTransporter::close()
{
	closed_read = true;
	std::cout << "waiting for read\n";
	read_thread->join();
	closed_write = true;
	std::cout << "waiting for write\n";
	write_thread->join();
	//just in case to work around issue with blocking read
	uint8_t dummy = 0;
	SDLNet_TCP_Send(sock, &dummy, 1);
	SDLNet_TCP_Close(sock);
}
