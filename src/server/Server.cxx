#include "Server.hxx"
#include <iomanip>
#include <cstdio>

#include "ServerEntity.hxx"

#include "Timer.hxx"
#include "Debug.hxx"

Server::Server() {
	_conn = new ClientsConnection(20000, boost::bind(&Server::sendOnLoginData, this, _1, _2));
	_gamestate = new ServerGameState(this);
	_map = new Map(128, 123);
}

Server::~Server() {
	delete _conn;
	delete _gamestate;
	delete _map;
}

void Server::sendOnLoginData(uint64_t client, int fd)
{
	std::list<Packet *> ps;

	PacketMap pm;
	pm.setMap(_map);
	ps.push_back((Packet*)(&pm));
	
	int size;
	uint8_t *b = ClientsConnection::crunchIntoBuffer(ps, &size);
	write(fd, b, size);
	delete[] b;
}

void Server::run() {
	_running = true;

	// _gamestate->get_entity(_gamestate->spawn_entity())
	// 	->get_unit_state_component()->setPosition(Position(400, 300));
	// _gamestate->get_entity(_gamestate->spawn_entity())
	// 	->get_unit_state_component()->setPosition(Position(200, 200));
	_conn->start();

	Timer timer;
	while (_running) {
		timer.reset_delta();

		std::list<Packet*> *packets = _conn->getPackets(100);
		std::list<Packet*>::iterator i = packets->begin();
		while(i != packets->end()) {

			Packet *p = *i;

			switch(p->type) {
				case PACKET_PING:
					DEBUG("got a ping request!");
					_conn->sendPacket(p, p->from);//logic
					delete p;
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
		delete packets;
		_gamestate->tick(timer.wall(), timer.delta());

		boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	}
	DEBUG("Cleaning up server...");
	_conn->stop();
	SDLNet_Quit();
}
