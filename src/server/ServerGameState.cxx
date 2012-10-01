#include <cstdio>
#include "ServerGameState.hxx"
#include "Event.hxx"
#include "Debug.hxx"
#include "Packet.hxx"
#include "Server.hxx"

#include "Unit.hxx"

ServerGameState::ServerGameState(Server * server) {
	_server = server;
	_next_id = 0;
}

ServerGameState::~ServerGameState() {
	std::map<EntityID, ServerEntity *>::iterator i = _entities.begin();
	while (i != _entities.end()) {
		delete i->second;
		++i;
	}
}

EntityID ServerGameState::spawn_unit() {
	EntityID id = _next_id;
	_next_id++;
	Unit* unit = new Unit(id, this);
	_entities[id] = unit;
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
	delete _entities[id];
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
		DEBUG("Received global event!");
		switch (event->event_type) {
			case EVENT_ENTITY_SPAWN: {
				((Unit*)get_entity(spawn_unit()))->set_position(Position(400, 300));	
			}
			case EVENT_TEST:{
				printf("Received a test event!\n");
				break;
			}
		}
	}
}

void ServerGameState::tick(double wallTime, double deltaTime){
	std::vector<ServerEntity*>::iterator it;
	for (it = clockReceivers.begin(); it < clockReceivers.end(); it++){
		(*it)->tick(wallTime, deltaTime);
	}
}

void ServerGameState::addClockListener(ServerEntity* toListen){
	clockReceivers.push_back(toListen);
	DEBUG("Added clock listener");
}

void ServerGameState::removeClockListener(ServerEntity* toListen){
	std::vector<ServerEntity*>::iterator it;

	for (it = clockReceivers.begin(); it<clockReceivers.end(); it++){
		if ((*it) == toListen){
			clockReceivers.erase(it);
		}
	}
}
