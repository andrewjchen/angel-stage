#include "string.h"
#include "Packet.hxx"
#include <unistd.h>

/////////////////////////////////////////////// CORE ////////////////////////////////////////////////////////////////////////////

Packet::Packet(uint8_t _type)
{
	type = _type;
}

void Packet::writeHeader(uint8_t *buf)
{
	buf[0] = type;
}

Packet *Packet::readByType(int _sock)
{
	Packet *p = 0;
	uint8_t _type = 0;
	read(_sock, &_type, 1);
	switch(_type)
	{
	case PACKET_PING:
		p = new PacketPing();
		break;
	case PACKET_DISCONNECT:
		p = new PacketDisconnect();
		break;
	case PACKET_EVENT:
		p = new PacketEvent();
		break;
	case PACKET_MAP:
		p = new PacketMap();
		break;
	}
	if(!p) return 0;
	p->readSock(_sock);
	return p;
}

/////////////////////////////////////////////// PACKET_PING ////////////////////////////////////////////////////////////////////////////

PacketPing::PacketPing() : Packet(PACKET_PING)
{
}

void PacketPing::readSock(int sock)
{
	read(sock, &pingstuff, 4);
}

int PacketPing::estimateSize()
{
	return headerSize + 4;
}

int PacketPing::writeToBuf(uint8_t *buf)
{
	writeHeader(buf);
	memcpy(buf + headerSize, &pingstuff, 4);
	
	return headerSize + 4;
}

/////////////////////////////////////////////// PACKET_DISCONNECT ////////////////////////////////////////////////////////////////////////////

PacketDisconnect::PacketDisconnect() : Packet(PACKET_DISCONNECT)
{
}

void PacketDisconnect::readSock(int sock)
{
	//no extra bytes
}

int PacketDisconnect::estimateSize()
{
	return headerSize;
}

int PacketDisconnect::writeToBuf(uint8_t *buf)
{
	writeHeader(buf);
	
	return headerSize;
}

/////////////////////////////////////////////// PACKET_EVENT ////////////////////////////////////////////////////////////////////////////

PacketEvent::PacketEvent() : Packet(PACKET_EVENT)
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

int PacketEvent::estimateSize()
{
	if(!event) return 0;
	return headerSize + ((Event*)event)->total_byte_count;
}

int PacketEvent::writeToBuf(uint8_t *buf)
{
	if(!event) return 0;
	writeHeader(buf);
	memcpy(buf + headerSize, event, ((Event*)event)->total_byte_count);
	
	return headerSize + ((Event*)event)->total_byte_count;
}

/////////////////////////////////////////////// PACKET_MAP ////////////////////////////////////////////////////////////////////////////

PacketMap::PacketMap() : Packet(PACKET_MAP)
{
	stuff = NULL;
	size = 0;
}

PacketMap::~PacketMap()
{
	if(stuff)
		delete[] stuff;
}

void PacketMap::readSock(int sock)
{
	read(sock, &size, 4);
	stuff = new uint8_t[size];
	read(sock, stuff, size);
}

int PacketMap::estimateSize()
{
	return headerSize + sizeof(size) + size;
}

int PacketMap::writeToBuf(uint8_t *buf)
{
	writeHeader(buf);
	memcpy(buf + headerSize, &size, sizeof(size));
	memcpy(buf + headerSize + sizeof(size), stuff, size);
	
	return headerSize + size;
}

uint8_t *PacketMap::getStuff()
{
	return stuff;
}

void PacketMap::setMap(Map *map)
{
	int s;
	stuff = map->save(&s);
	size = s;
}
