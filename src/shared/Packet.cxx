#include "string.h"
#include "Packet.hxx"

/////////////////////////////////////////////// CORE ////////////////////////////////////////////////////////////////////////////

Packet::Packet(uint8_t _type)
{
	type = _type;
}

void Packet::writeHeader(TCPsocket sock)
{
	SDLNet_TCP_Send(sock, &type, 1);
}

Packet *Packet::readByType(TCPsocket _sock, uint8_t _type)
{
	Packet *p = 0;
	switch(_type)
	{
	case PACKET_PING:
		p = new PacketPing(_type);
		break;
	case PACKET_DISCONNECT:
		p = new PacketDisconnect(_type);
		break;
	case PACKET_EVENT:
		p = new PacketEvent(_type);
		break;
	case PACKET_MAP:
		p = new PacketMap(_type);
		break;
	}
	if(!p) return 0;
	p->read(_sock);
	return p;
}

/////////////////////////////////////////////// PACKET_PING ////////////////////////////////////////////////////////////////////////////

PacketPing::PacketPing(uint8_t _type) : Packet(_type)
{
}

void PacketPing::read(TCPsocket sock)
{
	SDLNet_TCP_Recv(sock, &pingstuff, 4);
}

void PacketPing::write(TCPsocket sock)
{
	writeHeader(sock);
	SDLNet_TCP_Send(sock, &pingstuff, 4);
}

/////////////////////////////////////////////// PACKET_DISCONNECT ////////////////////////////////////////////////////////////////////////////

PacketDisconnect::PacketDisconnect(uint8_t _type) : Packet(_type)
{
}

void PacketDisconnect::read(TCPsocket sock)
{
	//no extra bytes
}

void PacketDisconnect::write(TCPsocket sock)
{
	writeHeader(sock);
}

/////////////////////////////////////////////// PACKET_EVENT ////////////////////////////////////////////////////////////////////////////

PacketEvent::PacketEvent(uint8_t _type) : Packet(_type)
{
	event = NULL;
}

PacketEvent::~PacketEvent()
{
	if(event) delete[] event;
}

void PacketEvent::read(TCPsocket sock)
{
	Event evthead;
	SDLNet_TCP_Recv(sock, &evthead, sizeof(evthead));
	int morebytes = evthead.total_byte_count - sizeof(evthead);
	uint8_t *buf = new uint8_t[evthead.total_byte_count];
	memcpy(buf, &evthead, sizeof(evthead));
	if(morebytes)
		SDLNet_TCP_Recv(sock, &(buf[sizeof(evthead)]), morebytes);
	event = buf;
}

void PacketEvent::setEvent(Event *_event)
{
	uint8_t *buf = new uint8_t[_event->total_byte_count];
	memcpy(buf, _event, _event->total_byte_count);
	event = buf;
}

Event* PacketEvent::getEvent(void)
{
	return (Event*)event;
}

void PacketEvent::write(TCPsocket sock)
{
	if(!event) return;
	writeHeader(sock);
	SDLNet_TCP_Send(sock, event, ((Event*)event)->total_byte_count);
}

/////////////////////////////////////////////// PACKET_MAP ////////////////////////////////////////////////////////////////////////////

PacketMap::PacketMap(uint8_t _type) : Packet(_type)
{
}

void PacketMap::read(TCPsocket sock)
{
	SDLNet_TCP_Recv(sock, &size, 4);
}

void PacketMap::write(TCPsocket sock)
{
	writeHeader(sock);
	SDLNet_TCP_Send(sock, &size, 4);
}
