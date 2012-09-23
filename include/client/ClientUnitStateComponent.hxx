#ifndef _CLIENT_UNIT_STATE_COMPONENT_HXX_
#define _CLIENT_UNIT_STATE_COMPONENT_HXX_

#include "UnitStateComponent.hxx"

class ClientUnitStateComponent : public UnitStateComponent {

public:
	ClientUnitStateComponent(Entity* entity);
	virtual ~ClientUnitStateComponent() {};
	virtual void feedback(UnitFeedbackEvent* event);
	virtual const Position & getPosition();

protected:
};

#endif
