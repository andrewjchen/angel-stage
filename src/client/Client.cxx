#include "Client.hxx"

#include "RenderSetup.hxx"
#include "Debug.hxx"
#include "ClientGlobals.hxx"
#include "Timer.hxx"

Client::Client() {

	if (!setup_rendering()){
		//TODO, do something
	}
	_renderer = new Renderer();
	_gamestate = new ClientGameState(_renderer);

	//_conn = new NetworkConnecter("172.16.0.111", 20000);
	_conn = new NetworkConnecter("127.0.0.1", 20000);
	_conn->start();
	_input = new InputManager(this, _renderer, _conn);

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
		std::list<Packet *> packets = _conn->getPacket(100);
		std::list<Packet*>::iterator i = packets.begin();
		while(i != packets.end()) {
			//std::cout << "got a packet!\n";
			Packet *p = *i;
			switch(p->type) {
				case PACKET_PING:
					//DEBUG("got a ping reply!");
					//DEBUG(((PacketPing*)p)->pingstuff);
					delete p;
					break;
				case PACKET_EVENT:
					//DEBUG("got an event!");
					_gamestate->react(((PacketEvent*)p)->getEvent());
					delete p;
					break;
				case PACKET_MAP:
					// DEBUG("got map data!");
					_renderer->addMap(new Map(((PacketMap*)p)->size));
					delete p;
					break;
			}
			i++;
		}
		_input->tick(timer.wall(), timer.delta());
		_renderer->render();
		//stop running if a quit is issued by keyboard
		_running = _input->keep_running();
	}

	PacketDisconnect p;
	_conn->sendPacket((Packet*)&p);
	DEBUG("trying to disconnect");
	_conn->disconnect();
}
