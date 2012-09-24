#ifndef SERVER_HXX
#define SERVER_HXX

#include "ServerGameState.hxx"
#include "ClientsConnection.hxx"

class Server {

public:
	Server();
	~Server();


	void run();
	void set_running(bool running) { _running = running; };


	ClientsConnection* get_clientsconnection() { return _conn; };
	ServerGameState* get_servergamestate() { return _gamestate; };

private:

	ClientsConnection* _conn;
	ServerGameState* _gamestate;

	bool _running;


};

#endif /* SERVER_HXX */