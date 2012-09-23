#ifndef INPUTMANAGER_HXX
#define INPUTMANAGER_HXX
#include "Renderer.hxx"
#include <allegro5/allegro.h>

class InputManager {
public:
	InputManager(Renderer * renderer);
	virtual ~InputManager() {};
	virtual void tick();
	virtual bool keep_running();
protected:
	virtual void react();
	ALLEGRO_EVENT_QUEUE * _event_queue;
	ALLEGRO_EVENT _current_event;
	Renderer * _renderer;
	bool _keep_running;
};

#endif /* INPUTMANAGER_HXX */
