#include <iostream>
#include "NetworkConnecter.hxx"

NetworkConnecter::NetworkConnecter(const char * server, uint16_t port){
	IPaddress ip;

	if(SDLNet_ResolveHost(&ip, server, port) != 0)
		throw "SDLNet_ResolveHost error";

	clientSock = SDLNet_TCP_Open(&ip);
	if(clientSock == NULL)
		throw "SDLNet_TCP_Open error";
}

NetworkConnecter::~NetworkConnecter(){
	if(clientSock)
		SDLNet_TCP_Close(clientSock);
}

void NetworkConnecter::connect(){
	if(clientSock == NULL)
		throw "clientSock is null!";
	PacketTransporter *nm = new PacketTransporter(clientSock);
	IPaddress *ip = SDLNet_TCP_GetPeerAddress(clientSock);
	nm->peer_ip = ((uint64_t)(ip->host) << 16) | (ip->port);
	boost::thread *new_peer_thread_read = new boost::thread(boost::bind(PacketTransporter::peer_thread_read, nm));
	boost::thread *new_peer_thread_write = new boost::thread(boost::bind(PacketTransporter::peer_thread_write, nm));

	nm->read_thread = new_peer_thread_read;
	nm->write_thread = new_peer_thread_write;

	packetTransport = nm;
}

void NetworkConnecter::disconnect(){
	packetTransport->close();
	clientSock = NULL;
	packetTransport = NULL;
}

bool NetworkConnecter::isConnected(){
	return packetTransport != NULL;
}

void NetworkConnecter::sendPacket(Packet* p){
	packetTransport->addTXPacket(p);
}

Packet* NetworkConnecter::getPacket(){
	return packetTransport->getRXPacket();
}
