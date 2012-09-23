#ifndef INPUTMANAGER_HXX
#define INPUTMANAGER_HXX
#include <allegro5/allegro.h>

class InputManager {
public:
	InputManager();
	virtual ~InputManager() {};
	virtual void tick();
protected:
	virtual void react();
	ALLEGRO_EVENT_QUEUE * _event_queue;
	ALLEGRO_EVENT _current_event;
};

#endif /* INPUTMANAGER_HXX */
