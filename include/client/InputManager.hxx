#ifndef INPUTMANAGER_HXX
#define INPUTMANAGER_HXX
#include "Renderer.hxx"
#include "NetworkConnecter.hxx"
#include <allegro5/allegro.h>

class InputManager {
public:
	InputManager(Renderer * renderer, NetworkConnecter * net_connecter);
	virtual ~InputManager() {};
	virtual void tick(double wall, double delta);
	virtual bool keep_running();
protected:
	virtual void react();
	ALLEGRO_EVENT_QUEUE * _event_queue;
	ALLEGRO_EVENT _current_event;
	Renderer * _renderer;
	bool _keep_running;
	NetworkConnecter * _net_connecter;
};

#endif /* INPUTMANAGER_HXX */
