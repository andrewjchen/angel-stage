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
    _xVel = 0;
    _yVel = 0;
    _state = UNIT_STATE_DEFAULT;
    _gamestate->add_clock_listener(this);
    _merge_partner = -1;

}

ServerUnit::~ServerUnit() {

}

/**************** EVENTS REACTIONS ************/

void ServerUnit::react(EntityEvent *event) {
    //DEBUG("ServerUnit id=" << _id << " received event");
    switch(event->header.event_type) {
        case EVENT_UNIT_SPLIT: {
            DEBUG("ServerUnit split event received");
            ServerUnit *newServerUnit = (ServerUnit *) (_gamestate
                                        ->get_entity(
                                            _gamestate->spawn_unit()));
            newServerUnit->set_size(_size/2.0);
            _size /=2.0;

            //TODO intelligently split units-- don't split on top of
            //existing units
            Position new_pos (_pos.get_x() + 20, _pos.get_y() + 20);
            newServerUnit->set_position(new_pos);
            break;
        }

        case EVENT_UNIT_MOVE: {

            //DEBUG("ServerUnit move event received");
            UnitMoveEvent *ume = (UnitMoveEvent *) event;
            set_goal(Position(
                         ume->xGoal,
                         ume->yGoal));


            break;

        }

        case EVENT_UNIT_MERGE: {
            DEBUG("Merge event received!");
            UnitMergeEvent *ume = (UnitMergeEvent *) event;

            _merge_partner = ume->partner;
            ServerUnit *partner = (ServerUnit * )_gamestate->get_entity(_merge_partner);

            //TODO midpoint not necesserily the best join point
            Position mid(
                (partner->get_position().get_x() + _pos.get_x())/2,
                (partner->get_position().get_y() + _pos.get_y())/2);
            partner->set_goal(mid);
            set_goal(mid);

            _state = UNIT_STATE_MERGING;

            break;
        }

    }

}


void ServerUnit::tick(double wallTime, double deltaT) {

    ///////////////// MOTION ///////////////////
    if (_goal.distance(_pos) < deltaT * UNIT_VELOCITY / 1000.0) {
        _pos.set_x(_goal.get_x());
        _pos.set_y(_goal.get_y());

        _xVel = 0;
        _yVel = 0;
    } else {
        double wantedNewX = _pos.get_x() + _xVel / _size * deltaT;
        double wantedNewY = _pos.get_y() + _yVel / _size * deltaT;
        //dont enter territory that is occupied
        if(!_gamestate->is_occupied(this,Position(wantedNewX, wantedNewY))) {
            _pos.set_x(wantedNewX);
            _pos.set_y(wantedNewY);
        }
    }

    ////////////////// MERGE /////////////////
    switch(_state) {
        case UNIT_STATE_MERGING: {
            if(_gamestate->get_entity(_merge_partner) != NULL) {
                ServerUnit *partner = (ServerUnit * ) _gamestate->get_entity(_merge_partner);
                if(_gamestate->two_units_touching(this, partner)) {
                    _size+= partner->get_size();
                    _gamestate->delete_entity(_merge_partner);
                    _state = UNIT_STATE_DEFAULT;
                }

            } else {
                _state = UNIT_STATE_DEFAULT;
            }
        }
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


void ServerUnit::set_goal(Position goal) {
    _goal.set_x(goal.get_x());
    _goal.set_y(goal.get_y());

    double dist = _goal.distance(_pos);
    double xdir = (_goal.get_x() - _pos.get_x()) / dist;
    double ydir = (_goal.get_y() - _pos.get_y()) / dist;

    _xVel = xdir * UNIT_VELOCITY/ 1000.0;
    _yVel = ydir * UNIT_VELOCITY/ 1000.0;

    _orientation = atan2(_xVel, _yVel)
                   + 3.14159265358979323846;
}

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
