/*
	Server main process
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <boost/thread/thread.hpp>
#include <signal.h>
#include <SDL/SDL.h>

#include "ClientsConnection.hxx"
#include "Packet.hxx"
#include "ServerGameState.hxx"
#include "ServerUnitStateComponent.hxx"
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

	ServerGameState *gs = new ServerGameState();
	ServerEntity* ent = new ServerEntity(0);

	gs->set_entity(0, ent);
	ent->set_gamestate(gs);
	ent->set_unit_state_component(new ServerUnitStateComponent(ent));

	//timekeeping
	uint32_t time0 = SDL_GetTicks();
	uint32_t prevTime = time0;

	SDLNet_Init();

	clientsConnection = new ClientsConnection(20000);
	clientsConnection->start();

	while(run)
	{
		clientsConnection->nm_mutex.lock();// lock the network managers
			std::list<PacketTransporter*>::iterator i = clientsConnection->packetTransporters.begin();
			while(i != clientsConnection->packetTransporters.end())
			{
				//process packets
				Packet *p;
				PacketTransporter *pt = *i;
				if(pt == 0) continue;
				while(pt && ((p = pt->getRXPacket()) != NULL))
				{
					//std::cout << "got a packet!\n";
					switch(p->type)
					{
					case PACKET_PING:
						std::cout << "got a ping request!\n";
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
						i = clientsConnection->packetTransporters.erase(i);
						break;
					case PACKET_EVENT:
						std::cout << "got an event!\n";
						gs->react(((PacketEvent*)p)->getEvent());
						delete p;
						break;
					}
				}

				i++;
			}
		clientsConnection->nm_mutex.unlock();

		//timekeeping
		uint32_t currentTime = SDL_GetTicks();
		gs->tick(currentTime - time0, currentTime - prevTime);
		prevTime = currentTime;

		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}

	std::cout << "Cleaning up server!\n";

	clientsConnection->stop();

	SDLNet_Quit();

	delete clientsConnection;
	delete gs;
	delete ent;
}
