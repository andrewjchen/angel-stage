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
	case 0x55:
		p = new PacketDisconnect(_sock, _type);
		break;
	}
	if(!p) return 0;
	p->read();
	return p;
}

/////////////////////////////////////////////// 0x55 ////////////////////////////////////////////////////////////////////////////

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
}
