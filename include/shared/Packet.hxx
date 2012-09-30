#ifndef PACKET_H
#define PACKET_H
#include <stdint.h>
#include "Event.hxx"

const uint8_t PACKET_PING           = 0x41;
const uint8_t PACKET_DISCONNECT     = 0x55;
const uint8_t PACKET_EVENT          = 0x45;
const uint8_t PACKET_MAP            = 0x4D;

/////////////////////////////////////////////// CORE ////////////////////////////////////////////////////////////////////////////

class Packet
{
public:
	Packet(uint8_t _type);
	static Packet *readByType(int _sock);
	virtual int estimateSize() = 0;
	virtual int writeToBuf(uint8_t *buf) = 0;

	uint8_t type;
	virtual ~Packet() {};
	uint64_t from;

protected:
	virtual void readSock(int sock) = 0;
	const static int headerSize = 1;
	void writeHeader(uint8_t *buf);
};

/////////////////////////////////////////////// PACKET_PING ////////////////////////////////////////////////////////////////////////////

class PacketPing: public Packet
{
public:
	PacketPing();
	int estimateSize();
	int writeToBuf(uint8_t *buf);

	uint32_t pingstuff;

protected:
	void readSock(int sock);
};

/////////////////////////////////////////////// PACKET_DISCONNECT ////////////////////////////////////////////////////////////////////////////

class PacketDisconnect: public Packet
{
public:
	PacketDisconnect();
	int estimateSize();
	int writeToBuf(uint8_t *buf);

protected:
	void readSock(int sock);
};

/////////////////////////////////////////////// PACKET_EVENT ////////////////////////////////////////////////////////////////////////////

class PacketEvent: public Packet
{
public:
	PacketEvent();
	~PacketEvent();
	int estimateSize();
	int writeToBuf(uint8_t *buf);
	void setEvent(Event *_event);
	Event *getEvent();

protected:
	uint8_t *event;
	void readSock(int sock);
};

/////////////////////////////////////////////// PACKET_MAP ////////////////////////////////////////////////////////////////////////////

class PacketMap: public Packet
{
public:
	PacketMap();
	int estimateSize();
	int writeToBuf(uint8_t *buf);

	int size;

protected:
	void readSock(int sock);
};

#endif
