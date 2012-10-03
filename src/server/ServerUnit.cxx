#include "ServerUnit.hxx"

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


ServerUnit::ServerUnit(
    EntityID id,
    ServerGameState *gamestate):
    ServerEntity(id, gamestate),
    _pos(0,0),
    _goal(0,0) {
    _orientation = 0;
    _size = 1.0;
    _gamestate->add_clock_listener(this);

}

ServerUnit::~ServerUnit() {

}

/**************** EVENTS REACTIONS ************/

void ServerUnit::react(EntityEvent* event) {
	//DEBUG("ServerUnit id=" << _id << " received event");
	switch(event->header.event_type) {
		case EVENT_UNIT_SPLIT: {
			//DEBUG("ServerUnit split event received");
			ServerUnit* newServerUnit = (ServerUnit*) (_gamestate
				->get_entity(
					_gamestate->spawn_unit()));

			Position new_pos (_pos.get_x() + 1, _pos.get_y() + 1);
			newServerUnit->set_position(new_pos);
			break;
		}

		case EVENT_UNIT_MOVE: {
			//DEBUG("ServerUnit move event received");
			UnitMoveEvent* ume = (UnitMoveEvent*) event;
			_goal.set_x(ume->xGoal);
			_goal.set_y(ume->yGoal);

			double dist = _goal.distance(_pos);
			double xdir = (_goal.get_x() - _pos.get_x()) / dist;
			double ydir = (_goal.get_y() - _pos.get_y()) / dist;

			_xVel = xdir * UNIT_VELOCITY/ 1000.0;
			_yVel = ydir * UNIT_VELOCITY/ 1000.0;

			_orientation = atan2(_xVel, _yVel) 
				+ 3.14159265358979323846;	

			break;

		}

		case EVENT_UNIT_MERGE: {
			UnitMergeEvent* ume = (UnitMergeEvent*) event;

			EntityID partner = ume->partner;

			_size+= 
				((ServerUnit*)_gamestate->get_entity(partner))
				->get_size();
			break;
		}
	}

}


void ServerUnit::tick(double wallTime, double deltaT) {
    //DEBUG("ServerUnit ticking : wall=" << wallTime << ", deltaT=" << deltaT);

    if (_goal.distance(_pos) < deltaT * UNIT_VELOCITY / 1000.0) {
        _pos.set_x(_goal.get_x());
        _pos.set_y(_goal.get_y());

        _xVel = 0;
        _yVel = 0;
    } else {
        double wantedNewX = _pos.get_x() + _xVel * deltaT;
        double wantedNewY = _pos.get_y() + _yVel * deltaT;

        _pos.set_x(wantedNewX);
        _pos.set_y(wantedNewY);

    }

    sync();
}

void ServerUnit::sync() {
    UnitFeedbackEvent *ufe = new UnitFeedbackEvent();
    memset(ufe, 0, sizeof(UnitFeedbackEvent));
    ufe->header.header.event_type = EVENT_UNIT_FEEDBACK;
    ufe->header.header.total_byte_count = sizeof(UnitFeedbackEvent);
    ufe->header.entity_id = _id;
    ufe->x = _pos.get_x();
    ufe->y = _pos.get_y();
    ufe->theta = _orientation;
    ufe->size = _size;
    PacketEvent pe;
    pe.setEvent((Event *)ufe); //does a memcopy
    delete ufe;
    _gamestate->get_server()->get_clientsconnection()->send_packet((Packet *)(&pe));
};




/**************** COMPONENTS ***************/

Position ServerUnit::get_position() {
    return _pos;
}

void ServerUnit::set_position(Position pos) {
    _pos = pos;
}

double ServerUnit::get_orientation() {
    return _orientation;
}

double ServerUnit::get_size() {
    return _size;
}

void ServerUnit::set_size(double size) {
    _size = size;
}
