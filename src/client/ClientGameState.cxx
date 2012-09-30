#include <iostream>
#include <cstdio>
#include "ClientGameState.hxx"
#include "UnitVisualComponent.hxx"
#include "ClientUnitStateComponent.hxx"
#include "Event.hxx"
#include "Debug.hxx"
#include <math.h>

ClientGameState::~ClientGameState() {
	std::map<EntityID, ClientEntity *>::iterator iter = _entities.begin();
	while (iter != _entities.end()) {
		delete iter->second;
		++iter;
	}
}

ClientEntity * ClientGameState::get_entity(EntityID id) {
	if ( _entities.count(id) == 0) { //if entity doens't exist
		//intialize new gamestate
		ClientEntity* ce = new ClientEntity(id);
		ce->set_gamestate(this);

		//components
		UnitVisualComponent *uvc = new UnitVisualComponent(ce);
		ClientUnitStateComponent *usc = new ClientUnitStateComponent(ce);
		ce->set_visual_component(uvc);
		ce->set_unit_state_component(usc);
		globalRenderer->addToUnitLayer(uvc);

		set_entity(id, ce);
	}
	return _entities[id];
}

void ClientGameState::set_entity(EntityID id, ClientEntity* entity) {
	_entities[id] = entity;
}

void ClientGameState::react(Event * event) {
	if (is_entity_event(event)) {
		EntityID id = ((EntityEvent *) event)->entity_id;
		ClientEntity * e = get_entity(id);
		if (e) {
			e->react((EntityEvent *) event);
		}
	} else if (is_global_event(event)) {
		DEBUG("Received global event!");
		switch (event->event_type) {
			case EVENT_ENTITY_SPAWN: { 
			 	UnitFeedbackEvent *ufe = (UnitFeedbackEvent*)(event);
				// std::cout << "Spawn an entity with id " << ufe->header.entity_id << "\n";
				// ClientEntity *ce = new ClientEntity(ufe->header.entity_id);
				// ce->set_gamestate(this);
				// UnitVisualComponent *uvc = new UnitVisualComponent(ce);
				// ClientUnitStateComponent *usc = new ClientUnitStateComponent(ce);
				// ce->set_visual_component(uvc);
				// ce->set_unit_state_component(usc);
				// globalRenderer->addToUnitLayer(ce->get_visual_component());
				// // ClientEntity* ce = get_entity(ufe->header.entity_id);
				// // ce->react((EntityEvent*)ufe);
				// set_entity(ufe->header.entity_id, ce);
				ClientEntity* ce = get_entity(ufe->header.entity_id);
				ce->react((EntityEvent*)ufe);
				break;
			}
			case EVENT_TEST: { 
				DEBUG("Received a test event!");
				break;
			}
		}
	}
}

void ClientGameState::tick(double wallTime, double deltaTime){
	std::vector<ClientComponent*>::iterator it;
	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		(*it)->tick(wallTime, deltaTime);
	}
}

void ClientGameState::addClockListener(ClientComponent* toListen){
	clockReceivers.push_back(toListen);
	DEBUG("Added clock listener");
}

void ClientGameState::removeClockListener(ClientComponent* toListen){
	//TODO test
//	clockReceivers.erase(
//		s td::remove(clockReceivers.begin(), clockReceivers.end(), toListen), clockReceivers.end() );
	std::vector<ClientComponent*>::iterator it;

	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		if( (*it) == toListen){
			clockReceivers.erase(it);
		}
	}
}

std::vector<ClientEntity *> * ClientGameState::get_entities_in_rect(const Position & p1,
												const Position & p2) {
	std::vector<ClientEntity *> * out = new std::vector<ClientEntity *>;
	double x1 = p1.getX();
	double x2 = p2.getX();
	double left  = x1 < x2 ? x1 : x2;
	double right = x1 < x2 ? x2 : x1;
	double y1 = p1.getY();
	double y2 = p2.getY();
	double bottom  = y1 < y2 ? y1 : y2;
	double top = y1 < y2 ? y2 : y1;
	Position top_left(left, top);
	Position bottom_right(right, bottom);
	std::map<EntityID, ClientEntity *>::iterator iter = _entities.begin();
	while (iter != _entities.end()) {
		if (iter->second->get_unit_state_component()->getPosition().in_rect(top_left, bottom_right)) {
			out->push_back(iter->second);
		}
		++iter;
	}
	return out;
}
