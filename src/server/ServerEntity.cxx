#include <cstdio>
#include "ServerEntity.hxx"
#include "EventTypes.hxx"
#include "Debug.hxx"

#include "ServerGameState.hxx"

void ServerEntity::react(EntityEvent * event) {
	DEBUG("Entity id=" << _id << " received event");
	switch (event->header.event_type) {
		case EVENT_UNIT_SPLIT: {
			DEBUG("unit split event received");
			ServerEntity* ent = gamestate->new_entity();
			Position my_pos = _unit_state_component->getPosition();

			//TODO smarter split
			Position new_pos(my_pos.getX() + 1, my_pos.getY() + 1);

			ent->get_unit_state_component()->setPosition(new_pos);
			break;
		}
		case EVENT_UNIT_MOVE :{
			UnitMoveEvent *ume = (UnitMoveEvent*) (event);
			_unit_state_component->setGoalPoint(Position(ume->xGoal, ume->yGoal));
			break;

		}
		case EVENT_UNIT_CHASE:
		{
			UnitChaseEvent *ume = (UnitChaseEvent*) (event);
			_unit_state_component->setGoalEntity(ume->target);
			break;
		}
		case EVENT_UNIT_MERGE :{
			UnitMergeEvent *ume = (UnitMergeEvent*) (event);
			_unit_state_component->mergeWith(ume->partner);


		}


	}
}
