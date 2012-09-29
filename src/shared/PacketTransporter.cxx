#include <iostream>
#include <boost/thread/thread.hpp>
#include <stdint.h>

#include "PacketTransporter.hxx"
#include "Packet.hxx"

PacketTransporter::PacketTransporter(TCPsocket _sock)
{
	sock = _sock;
	closed_read = closed_write = false;
	valid = true;
}

PacketTransporter::~PacketTransporter()
{
	if(valid)
		close();
}

void PacketTransporter::peer_thread_read(PacketTransporter *nm)
{
	SDLNet_SocketSet set;
	set = SDLNet_AllocSocketSet(1);
	SDLNet_TCP_AddSocket(set, nm->sock);

	while(!nm->closed_read)
	{
		int activity = SDLNet_CheckSockets(set, 0);
		if(activity == -1)
		{
			//error
			nm->queue_fake_disconnect();
			break;
		}
		
		if(activity > 0)
			nm->processNetworkRead();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_TCP_DelSocket(set, nm->sock);
	SDLNet_FreeSocketSet(set);
}

void PacketTransporter::peer_thread_write(PacketTransporter *nm)
{
	while(!nm->closed_write)
	{
		nm->processNetworkWrite();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
}

void PacketTransporter::processNetworkRead()
{
	uint8_t type;
	
	if(!valid)
		throw "PT is invalid!";

	std::cout << "processNetworkRead\n";

	if(SDLNet_TCP_Recv(sock, &type, 1) <= 0)
	{
		//error
		queue_fake_disconnect();
		return;
	}

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

void PacketTransporter::processNetworkWrite()
{
	if(!valid)
		throw "PT is invalid!";

	tx_mutex.lock();
		while(tx_queue.size() > 0)
		{
			Packet *pout = tx_queue.front();
			tx_queue.pop_front();
			// DEBUG("processNetworkWrite type = " << pout->type);
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
	
	SDLNet_TCP_Close(sock);
	
	valid = false;
	
	//clean packets in queue
	while(tx_queue.size() > 0)
	{
		Packet *p = tx_queue.front();
		tx_queue.pop_front();
		std::cout << "discardWrite" << p->type << "\n";
		delete p;
	}
	while(rx_queue.size() > 0)
	{
		Packet *p = rx_queue.front();
		rx_queue.pop_front();
		std::cout << "discardRead" << p->type << "\n";
		delete p;
	}

	delete read_thread;
	delete write_thread;
}

void PacketTransporter::queue_fake_disconnect()
{
	//hack
	Packet *p = new PacketDisconnect(PACKET_DISCONNECT);
	rx_mutex.lock();
		rx_queue.push_back(p);
	rx_mutex.unlock();
}
