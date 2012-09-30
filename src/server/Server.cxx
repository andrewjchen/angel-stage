#include "Server.hxx"
#include <iomanip>
#include <cstdio>

#include "ServerEntity.hxx"
#include "ServerUnitStateComponent.hxx"

#include "Timer.hxx"
#include "Debug.hxx"

Server::Server() {
	_conn = new ClientsConnection(20000);
	_gamestate = new ServerGameState(this);
}

Server::~Server() {
	delete _conn;
	delete _gamestate;
}

void Server::run() {
	_running = true;
	
	_gamestate->get_entity(1);

	_conn->start();

	Timer timer;
	while (_running) {
		timer.reset_delta();

		std::list<Packet*> packets = _conn->getPackets(100);
		std::list<Packet*>::iterator i = packets.begin();
		while(i != packets.end()) {

			//process packets
			Packet *p = *i;

			switch(p->type) {
				case PACKET_PING:
					DEBUG("got a ping request!");
					_conn->sendPacket(p, p->from);//logic
					break;
				case PACKET_DISCONNECT:
					std::cout << "got a disconnect packet!\n";
					std::cout << "Disconnected to client " << std::hex << p->from << "\n";
					printf("Disconnected to client %012lX\n", p->from);
					_conn->closeClient(p->from);
					delete p;
					break;
				case PACKET_EVENT:
					DEBUG("got an event!");
					_gamestate->react(((PacketEvent*)p)->getEvent());
					delete p;
					break;
			}
			i++;
		}
		_gamestate->tick(timer.wall(), timer.delta());

		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	DEBUG("Cleaning up server...");

	_conn->stop();
	SDLNet_Quit();

}
