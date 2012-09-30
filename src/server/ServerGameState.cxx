#include <cstdio>
#include "ServerGameState.hxx"
#include "Event.hxx"
#include "Debug.hxx"
#include "Packet.hxx"
#include "Server.hxx"

ServerGameState::ServerGameState(Server * server) {
	_server = server;
	_next_id = 0;
}

ServerGameState::~ServerGameState() {
	std::map<EntityID, ServerEntity *>::iterator i = _entities.begin();
	while (i != _entities.end()) {
		// ServerEntity * ent = i->second;
		// delete ent;
		delete i->second;
		++i;
	}
}

EntityID ServerGameState::spawn_entity() {
	EntityID id = _next_id;
	++_next_id;
	ServerEntity* ent = new ServerEntity(id, this);
	_entities[id] = ent;
	ent->set_unit_state_component(new ServerUnitStateComponent(ent));
	return id;
}

ServerEntity * ServerGameState::get_entity(EntityID id) {
	if (_entities.count(id)) {
		return _entities[id];
	} else {
		return NULL;
	}
}

void ServerGameState::set_entity(EntityID id, ServerEntity * entity) {
	_entities[id] = entity;
}

void ServerGameState::delete_entity(EntityID id) {

	DEBUG("NUM ENTITIES=" << _entities.size());
	_entities.erase(id);
	DEBUG("NUM ENTITIES=" << _entities.size());

	//notify client
	UnitDieEvent ude;
	ude.header.event_type = EVENT_ENTITY_DIE;
	ude.header.total_byte_count = sizeof(UnitDieEvent);
	ude.entity_id = id;

	PacketEvent* pe = new PacketEvent();
	pe->setEvent((Event*)&ude);
	_server->get_clientsconnection()->sendPacket(pe);
	delete pe;
}

void ServerGameState::react(Event * event) {
	if (is_entity_event(event)) {
		EntityID id = ((EntityEvent *) event)->entity_id;
		ServerEntity * e = get_entity(id);
		if (e) {
			e->react((EntityEvent *) event);
		}
	} else if (is_global_event(event)) {
		/* TODO: Do things. */
		if (event->event_type == EVENT_ENTITY_SPAWN) {
			get_entity(spawn_entity())->get_unit_state_component()->setPosition(Position(400, 300));
			// DEBUG("ERROR INCORRECT USE OF EVENT_ENTITY_SPAWN ON SERVER!");
		}
		printf("Received global event!\n");
		switch (event->event_type) {
		case EVENT_TEST:
			printf("Received a test event!\n");
			break;
		}
	}
}

void ServerGameState::tick(double wallTime, double deltaTime){
	std::vector<ServerComponent*>::iterator it;
	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		(*it)->tick(wallTime, deltaTime);
	}
}

void ServerGameState::addClockListener(ServerComponent* toListen){
	clockReceivers.push_back(toListen);
	DEBUG("Added clock listener");
}

void ServerGameState::removeClockListener(ServerComponent* toListen){
	//TODO test
//	clockReceivers.erase(
//		s td::remove(clockReceivers.begin(), clockReceivers.end(), toListen), clockReceivers.end() );
	std::vector<ServerComponent*>::iterator it;

	for(it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		if( (*it) == toListen){
			clockReceivers.erase(it);
		}
	}
}
