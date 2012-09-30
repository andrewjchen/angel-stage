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
		ServerEntity(id, gamestate) {
	_pose = NULL;
	_size = NULL;


}

Unit::~Unit() {
	delete _pose;
	delete _size;

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

			Position my_pos = _pose->get_position();
			Position new_pos (my_pos.getX() + 1, my_pos.getY() + 1);
			
			newUnit->get_pose()->set_position(new_pos);

		}

		case EVENT_UNIT_MOVE: {
			//UnitMoveEvent* ume = (UnitMoveEvent*) event;
		}



	}


	
}


/**************** COMPONENTS ***************/

Pose* Unit::get_pose() {
	//TODO exception if null?
	return _pose;
}

void Unit::set_pose(Pose* pose) {
	if(_pose) {
		delete _pose;
	}
	_pose = pose;
}

Size* Unit::get_size() {
	//TODO exception if null?
	return _size;
}

void Unit::set_size(Size* size) {
	if(_size) {
		delete _size;
	}
	_size = size;
}
