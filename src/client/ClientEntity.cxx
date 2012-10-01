#include "ClientEntity.hxx"
#include <cstdio>
#include "EventTypes.hxx"
#include "Debug.hxx"


ClientEntity::ClientEntity(EntityID id, ClientGameState* gamestate):
	Entity(id),
	_gamestate(gamestate) {

}

ClientEntity::~ClientEntity() {
}

void ClientEntity::react(EntityEvent * event) {
	//printf("Entity at %p received event!\n", this);
	// switch (event->header.event_type) {
	// 	case EVENT_UNIT_FEEDBACK:
	// 	case (EVENT_UNIT_MOVE):
	// 		if (_unit_state_component) {
	// 			UnitFeedbackEvent *ufe = (UnitFeedbackEvent*)(event);
	// 			// DEBUG("Move entity with id=" << ufe->header.entity_id << ", x=" <<ufe->x << ", y=" << ufe->y);
	// 			_unit_state_component->feedback(ufe);
	// 		}
	// 		break;
	// }
}

void ClientEntity::tick(double wallTime, double deltaT) {
	
}

ClientGameState* ClientEntity::get_gamestate() {
	return _gamestate;
}

