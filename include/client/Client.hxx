#ifndef Client_HXX
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
};

typedef struct Client Client;

#endif /* Client_HXX */
