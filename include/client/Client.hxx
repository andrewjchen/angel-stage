#ifndef Client_HXX
#define Client_HXX

#include "ClientGameState.hxx"
#include "NetworkConnecter.hxx"
#include "Renderer.hxx"
#include "InputManager.hxx"

class Client {

public:
	Client();
	~Client();


	void run();
	void set_running(bool running) { _running = running; };

 	NetworkConnecter* get_networkconnecter() { return _conn; };
	ClientGameState* get_clientgamestate() { return _gamestate; };

private:

	// ClientsConnection* _conn;
	NetworkConnecter* _conn;
	ClientGameState* _gamestate;
	Renderer* _renderer;
	InputManager* _input;

	bool _running;


};

#endif /* Client_HXX */