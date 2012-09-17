#ifndef NET_CLIENTS_H
#define NET_CLIENTS_H

#include "ClientsConnection.hxx"
#include "GameState.hxx"


/**
 * NetClients is the server-side client abstraction.
 * NetClients polls for Packets, and performs appropriate command to GameState
 * 
 * Server sends this the GameState to update clients.
 * 
 */
class NetClients
{
public: 
	NetClients(uint16_t port);
	~NetClients();

	void initialize();

	//polls for packets from clients, and acts
	void tick();

	void sendGameState(GameState state);


private:
	
	ClientsConnection ClientsConnection;


};
#endif