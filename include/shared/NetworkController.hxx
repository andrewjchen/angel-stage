#ifndef NETWORK_CONTROLLER_H
#define NETWORK_CONTROLLER_H 

#include "GameState.hxx"


/**
 * NetworkController gets packets frrom a NetworkConnection,
 * turns them into Events, and sends them to the gamestate to react.
 */
class NetworkController {

public:
	NetworkController(GameState );
	~NetworkController();


}