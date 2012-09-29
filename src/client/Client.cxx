#include "Client.hxx"

#include "RenderSetup.hxx"
#include "Debug.hxx"
#include "ClientGlobals.hxx"
#include "Timer.hxx"

Client::Client() {

	if (!setup_rendering()){
		//TODO, do something
	}
	SDLNet_Init();
	_renderer = new Renderer();
	_gamestate = new ClientGameState(_renderer);


	_conn = new NetworkConnecter("localhost", 20000);
	_conn->connect();
	_input = new InputManager(_renderer, _conn);

}

Client::~Client(){
	al_destroy_display(display);
	delete _renderer;
	delete _conn;
	delete _gamestate;
}

void Client::run() {
	_running = true;

	Timer timer;
	while(_running){
		timer.reset_delta();

		//get packets from server
		Packet* p;
		while((p = _conn->getPacket()) != NULL) {
			//std::cout << "got a packet!\n";
			switch(p->type) {
				case PACKET_PING:
					DEBUG("got a ping reply!");
					DEBUG(((PacketPing*)p)->pingstuff);
					delete p;
					break;
				case PACKET_EVENT:
					DEBUG("got an event!");
					_gamestate->react(((PacketEvent*)p)->getEvent());
					delete p;
					break;
				case PACKET_MAP:
					DEBUG("got map data!");
					_renderer->addMap(new Map(((PacketMap*)p)->size));
					delete p;
					break;
			}
		}
		_input->tick(timer.wall(), timer.delta());
		_renderer->render();
		//stop running if a quit is issued by keyboard
		_running = _input->keep_running();
	}

	Packet * p = new PacketDisconnect(PACKET_DISCONNECT);
	_conn->sendPacket(p);
	DEBUG("trying to disconnect");
	_conn->disconnect();
	SDLNet_Quit();
}
