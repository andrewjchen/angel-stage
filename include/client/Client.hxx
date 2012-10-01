#ifndef Client_HXX
#include "allegro5/allegro.h"
#define Client_HXX

class NetworkConnecter;
class ClientGameState;
class Renderer;
class InputManager;

struct Client {
	bool keep_running;
	NetworkConnecter* network_connector;
	ClientGameState* gamestate;
	Renderer* renderer;
	InputManager* input_manager;
	uint32_t display_width;
	uint32_t display_height;
	ALLEGRO_DISPLAY * display;
};

typedef struct Client Client;

#endif /* Client_HXX */
