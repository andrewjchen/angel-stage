#ifndef _SERVER_UNIT_SIZE_COMPONENT_HXX_
#define _SERVER_UNIT_SIZE_COMPONENT_HXX_

#include "ServerComponent.hxx"

/**
 * Size
 */
class Size : public ServerComponent {

public:
	Size(ServerEntity* entity);
	virtual ~Size();
	virtual void tick(double wallTime, double deltaT);

	double get_size();
	void set_size(double size);

protected:
	double _size;
};

#endif
