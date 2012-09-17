#ifndef PACKET_H
#define PACKET_H
#include <stdint.h>
#include "SDL/SDL_net.h"

const uint8_t PACKET_PING			= 0x41;
const uint8_t PACKET_DISCONNECT		= 0x55;

/////////////////////////////////////////////// CORE ////////////////////////////////////////////////////////////////////////////

class Packet
{
public:
	Packet(uint8_t _type);
	static Packet *readByType(TCPsocket _sock, uint8_t _type);
	virtual void write(TCPsocket sock) = 0;

	uint8_t type;

protected:
	virtual void read(TCPsocket sock) = 0;
	void writeHeader(TCPsocket sock);
};

/////////////////////////////////////////////// PACKET_PING ////////////////////////////////////////////////////////////////////////////

class PacketPing: public Packet
{
public:
	PacketPing(uint8_t _type);
	void write(TCPsocket sock);

	uint32_t pingstuff;

protected:
	void read(TCPsocket sock);
};

/////////////////////////////////////////////// PACKET_DISCONNECT ////////////////////////////////////////////////////////////////////////////

class PacketDisconnect: public Packet
{
public:
	PacketDisconnect(uint8_t _type);
	void write(TCPsocket sock);

protected:
	void read(TCPsocket sock);
};

#endif
