#ifndef _CLIENT_UNIT_STATE_COMPONENT_HXX_
#define _CLIENT_UNIT_STATE_COMPONENT_HXX_



#include "ClientComponent.hxx"
#include "EventTypes.hxx"
#include "Position.hxx"

class ClientUnitStateComponent : public ClientComponent {

public:
	ClientUnitStateComponent(ClientEntity* entity);
	virtual ~ClientUnitStateComponent() {};
	virtual void feedback(UnitFeedbackEvent* event);
	virtual const Position & getPosition();
	virtual void tick(double wallTime, double deltaT);
	double getTheta();
	double getSize();

protected:
	Position _pos;
	double _theta;


	double _size;
};

#endif
