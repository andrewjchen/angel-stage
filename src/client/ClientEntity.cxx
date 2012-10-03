#include "ClientEntity.hxx"
#include <cstdio>
#include "EventTypes.hxx"
#include "Debug.hxx"


ClientEntity::ClientEntity(EntityID id, ClientGameState *gamestate):
    Entity(id),
    _gamestate(gamestate) {

}

ClientEntity::~ClientEntity() {
}


ClientGameState *ClientEntity::get_gamestate() {
    return _gamestate;
}

