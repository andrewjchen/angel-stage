#include "ServerEntity.hxx"

ServerEntity::ServerEntity(EntityID id, ServerGameState* gamestate):
	Entity(id),
	_gamestate(gamestate) {

}

ServerEntity::~ServerEntity() {

}

void ServerEntity::react(EntityEvent* event) {
	
}


void ServerEntity::tick(double wallTime, double deltaT) {

}

ServerGameState* ServerEntity::get_gamestate() {
	return _gamestate;
}
