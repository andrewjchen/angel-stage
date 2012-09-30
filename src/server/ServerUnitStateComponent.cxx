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
	_size = 1;
	_state = STATE_NOT_MOVING;
	_target = 0xFFFFFFFF;
}

void ServerUnitStateComponent::tick(double wallTime, double deltaT) {

	/*
	// DEBUG("Tick: walltime=" << wallTime << ", deltaT=" << deltaT);
	_pos.setX(160 * cos(wallTime/1000.0) + 300);
	_pos.setY(160 * sin(wallTime/1000.0) + 400);
	_theta = -wallTime / 1000.0 -  3.14159265358979323846;
	*/
	switch(_state)
	{
	case STATE_NOT_MOVING:
		break;
	
	case STATE_CHASING_UNIT:
		{
			ServerEntity *target = _entity->get_gamestate()->get_entity(_target, false);
			if(!target)
			{
				_target = 0xFFFFFFFF;
				_state = STATE_NOT_MOVING;
				break;
			}
			setGoal(target->get_unit_state_component()->getPosition());
		}
	case STATE_CHASING_POINT:
		if (_goal.distance(_pos) < deltaT * UNIT_VELOCITY / 1000.0) {
			_pos.setX(_goal.getX());
			_pos.setY(_goal.getY());

			_xVel = 0;
			_yVel = 0;
		} else {
			_pos.setX(_pos.getX() + _xVel * deltaT);
			_pos.setY(_pos.getY() + _yVel * deltaT);
		}

		//TODO this is just a stupid size changing thing
		_size = 10.0 * sin(wallTime / 1000.0) + 10.0;

		//constructing packet to send
		UnitFeedbackEvent *ufe = new UnitFeedbackEvent();
		memset(ufe,  0, sizeof(UnitFeedbackEvent));
		ufe->header.header.event_type = EVENT_UNIT_MOVE;
		ufe->header.header.total_byte_count = sizeof(UnitFeedbackEvent);
		ufe->header.entity_id = _entity->get_id();
		ufe->x = _pos.getX();
		ufe->y = _pos.getY();
		ufe->theta = _theta;
		ufe->size = _size;
		PacketEvent pe;
		pe.setEvent((Event*)ufe);//does a memcopy
		delete ufe;

		//send
		_entity->get_gamestate()->get_server()->get_clientsconnection()->sendPacket((Packet*)(&pe));
		break;
	}
}

const Position & ServerUnitStateComponent::getPosition() {
	return _pos;
}

void ServerUnitStateComponent::setPosition(Position newpos) {
	_pos = newpos;
	_orbit_pos = newpos;//using orbitpos just to add weird motion

}

void ServerUnitStateComponent::setGoalEntity(EntityID target)
{
	_state = STATE_CHASING_UNIT;
	_target = target;
}

void ServerUnitStateComponent::setGoal(Position goal) {
	_goal = goal;

	double dist = _goal.distance(_pos);

	double xdir = (_goal.getX() - _pos.getX()) / dist;
	double ydir = (_goal.getY() - _pos.getY()) / dist;

	_xVel = xdir * UNIT_VELOCITY / 1000.0;
	_yVel = ydir * UNIT_VELOCITY / 1000.0;

	_theta = atan2(_xVel, _yVel);


}

void ServerUnitStateComponent::setGoalPoint(Position goal) {
	_state = STATE_CHASING_POINT;
	setGoal(goal);
}
