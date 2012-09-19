#ifndef SERVER_H
#define SERVER_H

#include "NetClients.hxx"
#include "GamePhysics.hxx"

class Server {
public:
	// static Server& getInstance();
	
	void run();
	
	void setRunning(const bool& b) { running = b; }
	
	// NetManager& getNetManager() { return net; }
	GamePhysics& getGamePhysics() { return phys; }
	
private:
	bool running;
	// NetManager net;
	NetClients net;
	GamePhysics phys;
	
	virtual ~Server() {};
	Server(const Server & server, port_t port) : net(port) {}
	const Server& operator=(const Server&) { return *this; }
};
#endif
