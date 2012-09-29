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

	ServerEntity* ent = new ServerEntity(0);
	_gamestate->set_entity(0, ent);
	ent->set_gamestate(_gamestate);
	ent->set_unit_state_component(new ServerUnitStateComponent(ent));

	_conn->start();

	Timer timer;
	while (_running) {
		timer.reset_delta();

		_conn->nm_mutex.lock();// lock the network managers
		std::list<PacketTransporter*>::iterator i = _conn->packetTransporters.begin();
		while(i != _conn->packetTransporters.end()) {

			//process packets
			Packet *p;
			PacketTransporter *pt = *i;

			// if null we don't process
			if(pt == 0) continue;

			//read packets loop
			while(pt && ((p = pt->getRXPacket()) != NULL)){
				switch(p->type) {
					case PACKET_PING:
						DEBUG("got a ping request!");
						pt->addTXPacket(p);//logic
						break;
					case PACKET_DISCONNECT:
						std::cout << "got a disconnect packet!\n";
						//std::cout << "Disconnected to client " << std::hex << pt->peer_ip << "\n";
						printf("Disconnected to client %012lX\n", pt->peer_ip);
						pt->close(); //logic
						delete p;
						delete pt;
						pt = 0;
						i = _conn->packetTransporters.erase(i);
						break;
					case PACKET_EVENT:
						DEBUG("got an event!");
						_gamestate->react(((PacketEvent*)p)->getEvent());
						delete p;
						break;
					}
			}
			i++;
		}
		_conn->nm_mutex.unlock();
		_gamestate->tick(timer.wall(), timer.delta());

		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	DEBUG("Cleaning up server...");

	_conn->stop();
	SDLNet_Quit();

	delete ent;

}
