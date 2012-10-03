#ifndef INPUTMANAGER_HXX
#define INPUTMANAGER_HXX
#include "Renderer.hxx"
#include "NetworkConnecter.hxx"
#include "ClientGameState.hxx"
#include <allegro5/allegro.h>
#include "Entity.hxx"

#include <map>
#include <vector>

struct Client;
class ClientEntity;

class InputManager {
public:
    InputManager(Client *client);
    virtual ~InputManager();
    virtual void tick(double wall, double delta);

protected:
	virtual void react();
	virtual void select_from_rect();

	virtual void send_packet(Event* e);

	ALLEGRO_EVENT_QUEUE * _event_queue;
	ALLEGRO_EVENT _current_event;

    Client *_client;
    Position _mouse_corner_start;
    Position _mouse_corner_end;
    ALLEGRO_KEYBOARD_STATE _keyboard;
    ALLEGRO_MOUSE_STATE _mouse;
    std::vector<ClientEntity *> * _selected_units;
};

#endif /* INPUTMANAGER_HXX */
