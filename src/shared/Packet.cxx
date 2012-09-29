#include "string.h"
#include "Packet.hxx"
#include <unistd.h>

/////////////////////////////////////////////// CORE ////////////////////////////////////////////////////////////////////////////

Packet::Packet(uint8_t _type)
{
	type = _type;
}

void Packet::writeHeader(int sock)
{
	write(sock, &type, 1);
}

Packet *Packet::readByType(int _sock)
{
	Packet *p = 0;
	uint8_t _type = 0;
	read(_sock, &_type, 1);
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
	p->readSock(_sock);
	return p;
}

/////////////////////////////////////////////// PACKET_PING ////////////////////////////////////////////////////////////////////////////

PacketPing::PacketPing(uint8_t _type) : Packet(_type)
{
}

void PacketPing::readSock(int sock)
{
	read(sock, &pingstuff, 4);
}

void PacketPing::writeSock(int sock)
{
	writeHeader(sock);
	write(sock, &pingstuff, 4);
}

/////////////////////////////////////////////// PACKET_DISCONNECT ////////////////////////////////////////////////////////////////////////////

PacketDisconnect::PacketDisconnect(uint8_t _type) : Packet(_type)
{
}

void PacketDisconnect::readSock(int sock)
{
	//no extra bytes
}

void PacketDisconnect::writeSock(int sock)
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

void PacketEvent::readSock(int sock)
{
	Event evthead;
	read(sock, &evthead, sizeof(evthead));
	int morebytes = evthead.total_byte_count - sizeof(evthead);
	uint8_t *buf = new uint8_t[evthead.total_byte_count];
	memcpy(buf, &evthead, sizeof(evthead));
	if(morebytes)
		read(sock, &(buf[sizeof(evthead)]), morebytes);
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

void PacketEvent::writeSock(int sock)
{
	if(!event) return;
	writeHeader(sock);
	write(sock, event, ((Event*)event)->total_byte_count);
}

/////////////////////////////////////////////// PACKET_MAP ////////////////////////////////////////////////////////////////////////////

PacketMap::PacketMap(uint8_t _type) : Packet(_type)
{
}

void PacketMap::readSock(int sock)
{
	read(sock, &size, 4);
}

void PacketMap::writeSock(int sock)
{
	writeHeader(sock);
	write(sock, &size, 4);
}
