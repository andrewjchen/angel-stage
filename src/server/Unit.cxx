#include "Unit.hxx"

//ctor: null
#include <cstdlib>
//SYNC:
#include <string.h>//memset
#include "Packet.hxx"//sending packet
#include "Server.hxx"//getting the nic
//react: events
#include "EventTypes.hxx"
//react: gamestate
#include "ServerGameState.hxx"
//react: motion
#include <math.h>

//nice debugging
#include "Debug.hxx"


Unit::Unit(
	EntityID id, 
	ServerGameState* gamestate): 
		ServerEntity(id, gamestate),
		_pos(0,0),
		_goal(0,0) {
	_orientation = 0; _size = 1.0;
	_gamestate->addClockListener(this);

}

Unit::~Unit() {

}

/**************** EVENTS REACTIONS ************/

void Unit::react(EntityEvent* event) {
	DEBUG("Unit id=" << _id << " received event");
	switch(event->header.event_type) {
		case EVENT_UNIT_SPLIT: {
			DEBUG("unit split event received");
			Unit* newUnit = (Unit*) (_gamestate
				->get_entity(
					_gamestate->spawn_unit()));

			Position new_pos (_pos.getX() + 1, _pos.getY() + 1);
			newUnit->set_position(new_pos);
		}

		case EVENT_UNIT_MOVE: {
			DEBUG("unit move event received");
			UnitMoveEvent* ume = (UnitMoveEvent*) event;
			_goal.setX(ume->xGoal);
			_goal.setY(ume->yGoal);

			double dist = _goal.distance(_pos);
			double xdir = (_goal.getX() - _pos.getX()) / dist;
			double ydir = (_goal.getY() - _pos.getY()) / dist;

			_xVel = xdir * UNIT_VELOCITY / 1000.0;
			_yVel = ydir * UNIT_VELOCITY / 1000.0;

			_orientation = atan2(_xVel, _yVel) 
				+ 3.14159265358979323846;	

		}



	}


	
}


void Unit::tick(double wallTime, double deltaT) {
	//DEBUG("unit ticking : wall=" << wallTime << ", deltaT=" << deltaT);

	if (_goal.distance(_pos) < deltaT * UNIT_VELOCITY / 1000.0) {
		_pos.setX(_goal.getX());
		_pos.setY(_goal.getY());

		_xVel = 0;
		_yVel = 0;
	} else {
		double wantedNewX = _pos.getX() + _xVel * deltaT;
		double wantedNewY = _pos.getY() + _yVel * deltaT;
		
		_pos.setX(wantedNewX);
		_pos.setY(wantedNewY);
			
	}	

	sync();
}

void Unit::sync() {
	UnitFeedbackEvent *ufe = new UnitFeedbackEvent();
	memset(ufe, 0, sizeof(UnitFeedbackEvent));
	ufe->header.header.event_type = EVENT_UNIT_MOVE;
	ufe->header.header.total_byte_count = sizeof(UnitFeedbackEvent);
	ufe->header.entity_id = _id;
	ufe->x = _pos.getX();
	ufe->y = _pos.getY();
	ufe->theta = _orientation;
	ufe->size = _size;
	PacketEvent pe;
	pe.setEvent((Event*)ufe);//does a memcopy
	delete ufe;
	_gamestate->get_server()->get_clientsconnection()->sendPacket((Packet*)(&pe));
};




/**************** COMPONENTS ***************/

Position Unit::get_position() {
	return _pos;
}

void Unit::set_position(Position pos) {
	_pos = pos;
}

double Unit::get_size() {
	return _size;
}

void Unit::set_size(double size) {
	_size = size;
}
