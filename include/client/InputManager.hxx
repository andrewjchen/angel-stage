#ifndef INPUTMANAGER_HXX
#define INPUTMANAGER_HXX
#include "Renderer.hxx"
#include "NetworkConnecter.hxx"
#include "ClientGameState.hxx"
#include <allegro5/allegro.h>
#include "Entity.hxx"

#include <map>
#include <vector>

class Client;
class ClientEntity;

class InputManager {
public:
	InputManager(Client* client, Renderer * renderer, NetworkConnecter * net_connecter, ClientGameState * gamestate);
	virtual ~InputManager() {};
	virtual void tick(double wall, double delta);
	virtual bool keep_running();

protected:
	virtual void react();
	virtual void select_from_rect();
	ALLEGRO_EVENT_QUEUE * _event_queue;
	ALLEGRO_EVENT _current_event;
	Renderer * _renderer;
	bool _keep_running;
	NetworkConnecter * _net_connecter;

	Client* _client;
	ClientGameState* _gamestate;
	Position _mouse_corner_start; // Screen coordinate
	Position _mouse_corner_end; // Screen coordinate
	ALLEGRO_KEYBOARD_STATE _keyboard;
	ALLEGRO_MOUSE_STATE _mouse;
	std::vector<ClientEntity *> * _selected_units;
};

#endif /* INPUTMANAGER_HXX */
