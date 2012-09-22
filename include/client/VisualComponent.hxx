#ifndef _VISUAL_COMPONENT_HXX_
#define _VISUAL_COMPONENT_HXX_

#include "Component.hxx"
#include "EventTypes.hxx"

class VisualComponent : public Component {

public:
	VisualComponent(Entity* entity);
	virtual ~VisualComponent() {};
	virtual void tick(double wallTime, double deltaT);
};

#endif /* _VISUAL_COMPONENT_HXX_ */
