#include <iostream>
#include <iomanip>
#include <cstdio>
#include "ClientsConnection.hxx"
#include "Packet.hxx"
#include "Event.hxx"
#include "EventTypes.hxx"

#include <math.h>
#include "Debug.hxx"

ClientsConnection::ClientsConnection(uint16_t port)
{

	IPaddress ip;
	
	if(SDLNet_ResolveHost(&ip, NULL, port) != 0)
		throw "SDLNet_ResolveHost error";
	
	listenSock = SDLNet_TCP_Open(&ip);
	if(listenSock == NULL)
		throw "SDLNet_TCP_Open error";
	
	running = false;
	stopped = false;
}

ClientsConnection::~ClientsConnection()
{
	if(running)
		stop();
}

void ClientsConnection::start()
{
	if(running)
		throw "Already running!";
	if(stopped)
		throw "Stopped! (and therefore invalid)";

	running = true;
	listenThread = new boost::thread(boost::bind(&ClientsConnection::listen, this));
}

void ClientsConnection::stop()
{
	stopped = true;
	running = false;
	
	listenThread->join();
	delete listenThread;
	listenThread = NULL;
	if(listenSock)
	{
		SDLNet_TCP_Close(listenSock);
		listenSock = NULL;
	}
}

void ClientsConnection::tick()
{
	if(!running)
		throw "Not running!";
	if(stopped)
		throw "Stopped! (and therefore invalid)";
	if(listenSock == NULL)
		throw "listenSock is null!";

		
	TCPsocket clientSock;
	//on client join
	while((clientSock = SDLNet_TCP_Accept(listenSock)) != NULL)
	{
		PacketTransporter *pt = new PacketTransporter(clientSock);
		IPaddress *ip = SDLNet_TCP_GetPeerAddress(clientSock);
		pt->peer_ip = ((uint64_t)(ip->host) << 16) | (ip->port);
		printf("Connected to client %012lX\n", pt->peer_ip);
		boost::thread *new_peer_thread_read = new boost::thread(boost::bind(PacketTransporter::peer_thread_read, pt));
		boost::thread *new_peer_thread_write = new boost::thread(boost::bind(PacketTransporter::peer_thread_write, pt));
		
		pt->read_thread = new_peer_thread_read;
		pt->write_thread = new_peer_thread_write;
		
		//stuff to send to client on loginpt
		PacketMap *pm = new PacketMap(PACKET_MAP);
		pm->size = 48;
		pt->addTXPacket(pm);
		
		UnitFeedbackEvent *ufe = new UnitFeedbackEvent();
		memset(ufe,  0, sizeof(UnitFeedbackEvent));
		ufe->header.header.event_type = EVENT_ENTITY_SPAWN;
		ufe->header.header.total_byte_count = sizeof(UnitFeedbackEvent);
		ufe->header.entity_id = 12345;
		ufe->x = 2;
		ufe->y = 2;

		ufe->theta = 45.0;
		PacketEvent *pe = new PacketEvent(PACKET_EVENT);
		pe->setEvent((Event*)ufe);
		delete ufe;
		pt->addTXPacket(pe);
		
		nm_mutex.lock();
			packetTransporters.push_back(pt);
		nm_mutex.unlock();
	}
}

void ClientsConnection::listen(){
	try {
		while (running) {
			this->tick();
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		}
	} catch (const char *e){
		std::cout << e << std::endl;
	}
}

void ClientsConnection::sendPacket(Packet *p, uint64_t client)
{
	nm_mutex.lock();
		for(std::list<PacketTransporter*>::iterator i = packetTransporters.begin(); i != packetTransporters.end(); i++)
		{
			PacketTransporter *pt = *i;
			if(pt == NULL) continue;
			if(pt->peer_ip == client || client == 0)
			{
				pt->addTXPacket(p);
				break;
			}
		}
	nm_mutex.unlock();
}

std::list<Packet*> ClientsConnection::getPackets(){
	std::list<Packet*> retu;

	// nm_mutex.lock();

	// std::list<PacketTransporter*>::iterator i;
	// for(i = packetTransporters.begin(); i!=packetTransporters.end(); i++){
	// 	Packet* p;
	// 	PacketTransporter* pt = *i;
	// 	if(pt == 0){
	// 		continue;
	// 	}

	// 	while(pt && ((p = pt->getRXPacket()) != NULL)){
	// 		retu.push_back(p);
	// 	}

	// }

	// nm_mutex.unlock();

	return retu;

}