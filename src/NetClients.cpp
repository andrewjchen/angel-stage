#include "NetClients.hxx"


NetClients::NetClients(uint16_t port): clientAccepter(port){

}

NetClients::~NetClients(){

}

void NetClients::initialize(){
	clientAccepter.start();
}

void NetClients::tick(){

}

void NetClients::sendGameState(GameState state){
	
}