#ifndef _UNIT_VISUAL_COMPONENT_HXX_
#define _UNIT_VISUAL_COMPONENT_HXX_
#include "VisualComponent.hxx"
#include "ClientGlobals.hxx"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class UnitVisualComponent : VisualComponent {
public:
	UnitVisualComponent(Entity * entity);
	virtual ~UnitVisualComponent() {};
	virtual void tick(double wallTime, double deltaT);
	virtual void render(const Position & viewpoint);
protected:
	int32_t _half_bitmap_width;
	int32_t _half_bitmap_height;
	ALLEGRO_BITMAP * _bitmap;
};

#endif /* _UNIT_VISUAL_COMPONENT_HXX_ */
