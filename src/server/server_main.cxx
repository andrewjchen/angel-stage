/*
	Server main process
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <boost/thread/thread.hpp>
#include <signal.h>

#include "ClientsConnection.hxx"
#include "Packet.hxx"
#include "GameState.hxx"
#include "UnitStateComponent.hxx"

#include "Debug.hxx"

ClientsConnection * clientsConnection;
int run;

void sigint_handler(int sig)
{
	run = 0;
}

int main(int argc, char **argv)
{
	run = 1;
	signal(SIGINT, sigint_handler);
	
	std::cout << "Starting server!\n";
	
	GameState *gs = new GameState();
	Entity* ent = new Entity(0);
	gs->set_entity(0, ent);
	ent->set_gamestate(gs);
	ent->set_unit_state_component(new UnitStateComponent(ent));

	

	
	SDLNet_Init();

	clientsConnection = new ClientsConnection(20000);
	clientsConnection->start();
	
	double wallTime= 0;
	
	while(run) 
	{
		if(!clientsConnection) continue;//if null, don't act

		clientsConnection->nm_mutex.lock();// lock the network managers
			for(int i = 0; i < clientsConnection->packetTransporters.size(); i++)
			{
				//process packets
				Packet *p;
				PacketTransporter *nm = clientsConnection->packetTransporters[i];
				if(nm == 0) continue;
				while(nm && ((p = nm->getRXPacket()) != NULL))
				{
					//std::cout << "got a packet!\n";
					switch(p->type)
					{
					case PACKET_PING:
						std::cout << "got a ping request!\n";
						nm->addTXPacket(p);//logic
						break;
					case PACKET_DISCONNECT:
						std::cout << "got a disconnect packet!\n";
						//std::cout << "Disconnected to client " << std::hex << nm->peer_ip << "\n";
						printf("Disconnected to client %012lX\n", nm->peer_ip);
						nm->close(); //logic
						delete p;
						nm = 0;
						clientsConnection->packetTransporters[i] = 0; //TODO delete members
						break;
					case PACKET_EVENT:
						std::cout << "got an event!\n";
						gs->react(((PacketEvent*)p)->event);
						delete p;
						break;
					}
				}
			}
		clientsConnection->nm_mutex.unlock();
		wallTime+= .001;
		//DEBUG(wallTime);
		gs->tick(wallTime, .001); // TODO
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	std::cout << "Cleaning up server!\n";
	
	clientsConnection->stop();
	
	SDLNet_Quit();
	
	delete clientsConnection;
	delete gs;
}
