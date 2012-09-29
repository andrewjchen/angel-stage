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
}

void ServerUnitStateComponent::tick(double wallTime, double deltaT){
	// DEBUG("Tick: walltime=" << wallTime << ", deltaT=" << deltaT);
	_pos.setX(10* cos(wallTime/1000.0) + 0);
	_pos.setY(10* sin(wallTime/1000.0) + 0);

	//constructing packet to send
	UnitFeedbackEvent *ufe = new UnitFeedbackEvent();
	ufe->header.header.event_type = EVENT_UNIT_MOVE;
	ufe->header.header.total_byte_count = sizeof(UnitFeedbackEvent);
	ufe->header.entity_id = _entity->get_id();
	ufe->x = _pos.getX();
	ufe->y = _pos.getY();
	ufe->theta = _theta;
	PacketEvent *pe = new PacketEvent(PACKET_EVENT);
	pe->setEvent((Event*)ufe);//does a memcopy
	delete ufe;

	//send
	_entity->get_gamestate()->get_server()->get_clientsconnection()->sendPacket(pe);


}

const Position & ServerUnitStateComponent::getPosition() {
	return _pos;
}
