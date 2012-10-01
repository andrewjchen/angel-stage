#ifndef _UNIT_VISUAL_COMPONENT_HXX_
#define _UNIT_VISUAL_COMPONENT_HXX_
#include "VisualComponent.hxx"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "InputManager.hxx"

struct Client;

class UnitVisualComponent : public VisualComponent {
public:
	UnitVisualComponent(ClientEntity * entity);
	virtual ~UnitVisualComponent() {};
	virtual void tick(double wallTime, double deltaT);
	virtual void render(const Position & viewpoint, Client * client);
protected:
	int32_t _half_bitmap_width;
	int32_t _half_bitmap_height;
	ALLEGRO_BITMAP * _bitmap;
};

#endif /* _UNIT_VISUAL_COMPONENT_HXX_ */
