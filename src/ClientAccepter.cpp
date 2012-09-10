#include <iostream>
#include "ClientAccepter.h"

ClientAccepter::ClientAccepter(uint16_t port)
{
	IPaddress ip;
	
	if(SDLNet_ResolveHost(&ip, NULL, port) != 0)
		throw "SDLNet_ResolveHost error";
	
	listenSock = SDLNet_TCP_Open(&ip);
	if(listenSock == NULL)
		throw "SDLNet_TCP_Open error";
}

ClientAccepter::~ClientAccepter()
{
	if(listenSock)
		SDLNet_TCP_Close(listenSock);
}

void ClientAccepter::start(){
//	boost::thread listener( &ClientAccepter::listen );
//	boost::thread listener( this->listen );

//boost::thread* thr = new boost::thread(boost::bind(&Foo::some_function, this));	
		listenThread = new boost::thread(
			boost::bind(&ClientAccepter::listen, this));

}

void ClientAccepter::tick()
{
	if(listenSock == NULL)
		throw "listenSock is null!";
	TCPsocket clientSock;
	while((clientSock = SDLNet_TCP_Accept(listenSock)) != NULL)
	{
		//std::cout << "asdf\n";
		//SDLNet_TCP_Close(clientSock);
		PacketTransporter *nm = new PacketTransporter(clientSock);
		boost::thread *new_peer_thread_read = new boost::thread(boost::bind(PacketTransporter::peer_thread_read, nm));
		boost::thread *new_peer_thread_write = new boost::thread(boost::bind(PacketTransporter::peer_thread_write, nm));
		
		nm->read_thread = new_peer_thread_read;
		nm->write_thread = new_peer_thread_write;
		
		nm_mutex.lock();
			packetTransporters.push_back(nm);
		nm_mutex.unlock();
	}
}

void ClientAccepter::listen(){
	try {
		while (1) {
			this->tick();
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		}
		delete this;	
	} catch (const char *e){
		std::cout << e << std::endl;
	}



}
