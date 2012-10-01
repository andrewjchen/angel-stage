#include "Unit.hxx"

//ctor: null
#include <cstdlib>
//react: events
#include "EventTypes.hxx"
//react: gamestate
#include "ServerGameState.hxx"

//nice debugging
#include "Debug.hxx"


Unit::Unit(
	EntityID id, 
	ServerGameState* gamestate): 
		ServerEntity(id, gamestate),
		_pos(0,0) {
	_orientation = 0;
	_size = 1.0;

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
			//UnitMoveEvent* ume = (UnitMoveEvent*) event;
		}



	}


	
}


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
