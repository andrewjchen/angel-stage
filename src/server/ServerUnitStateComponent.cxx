#include "ServerUnitStateComponent.hxx"
#include "Server.hxx"
#include "ServerGameState.hxx"
#include "ServerEntity.hxx"
#include "ClientsConnection.hxx"
#include <math.h>
#include "Debug.hxx"

#include "EventTypes.hxx"
#include "Packet.hxx"

ServerUnitStateComponent::ServerUnitStateComponent(ServerEntity* entity) : ServerComponent(entity) {
	entity->get_gamestate()->addClockListener(this);
	DEBUG("Added unit state component");
	_orbit_pos.setX(_entity->get_id());
	_orbit_pos.setY(_entity->get_id());
}

void ServerUnitStateComponent::tick(double wallTime, double deltaT){
	// DEBUG("Tick: walltime=" << wallTime << ", deltaT=" << deltaT);
	_pos.setX(160 * cos(wallTime/1000.0) + 300);
	_pos.setY(160 * sin(wallTime/1000.0) + 400);
	_theta = -wallTime / 1000.0 -  3.14159265358979323846;

	//constructing packet to send
	UnitFeedbackEvent *ufe = new UnitFeedbackEvent();
	memset(ufe,  0, sizeof(UnitFeedbackEvent));
	ufe->header.header.event_type = EVENT_UNIT_MOVE;
	ufe->header.header.total_byte_count = sizeof(UnitFeedbackEvent);
	ufe->header.entity_id = _entity->get_id();
	ufe->x = _pos.getX();
	ufe->y = _pos.getY();
	ufe->theta = _theta;
	PacketEvent pe;
	pe.setEvent((Event*)ufe);//does a memcopy
	delete ufe;

	//send
	_entity->get_gamestate()->get_server()->get_clientsconnection()->sendPacket((Packet*)(&pe));

	// delete pe;
}

const Position & ServerUnitStateComponent::getPosition() {
	return _pos;
}

void ServerUnitStateComponent::setPosition(Position newpos) {
	_pos = newpos;
	_orbit_pos = newpos;//using orbitpos just to add weird motion

}
