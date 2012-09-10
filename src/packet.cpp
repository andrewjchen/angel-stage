#include "packet.h"

/////////////////////////////////////////////// CORE ////////////////////////////////////////////////////////////////////////////

Packet::Packet(TCPsocket _sock, uint8_t _type)
{
	sock = _sock;
	type = _type;
}

void Packet::writeHeader()
{
	SDLNet_TCP_Send(sock, &type, 1);
}

Packet *Packet::readByType(TCPsocket _sock, uint8_t _type)
{
	Packet *p = 0;
	switch(_type)
	{
	case PACKET_PING:
		p = new PacketPing(_sock, _type);
		break;
	case PACKET_DISCONNECT:
		p = new PacketDisconnect(_sock, _type);
		break;
	}
	if(!p) return 0;
	p->read();
	return p;
}

/////////////////////////////////////////////// PACKET_PING ////////////////////////////////////////////////////////////////////////////

PacketPing::PacketPing(TCPsocket _sock, uint8_t _type) : Packet(_sock, _type)
{
}

void PacketPing::read()
{
	SDLNet_TCP_Recv(sock, &pingstuff, 4);
}

void PacketPing::write()
{
	writeHeader();
	SDLNet_TCP_Send(sock, &pingstuff, 4);
}

/////////////////////////////////////////////// PACKET_DISCONNECT ////////////////////////////////////////////////////////////////////////////

PacketDisconnect::PacketDisconnect(TCPsocket _sock, uint8_t _type) : Packet(_sock, _type)
{
}

void PacketDisconnect::read()
{
	//no extra bytes
}

void PacketDisconnect::write()
{
	writeHeader();
	//just in case to work around issue with blocking read
	uint8_t dummy = 0;
	SDLNet_TCP_Send(sock, &dummy, 1);
}
