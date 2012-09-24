/*
	Server main process
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <boost/thread/thread.hpp>
#include <boost/timer.hpp>
#include <signal.h>

#include "ClientsConnection.hxx"
#include "Packet.hxx"
#include "ServerGameState.hxx"
#include "ServerUnitStateComponent.hxx"
#include "Debug.hxx"

#include <math.h>

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
	boost::timer *time0 = new boost::timer();
	boost::timer *prevTime = new boost::timer();

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
				

				//read packets loop
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

				//send feedback event
				UnitFeedbackEvent *ufe = new UnitFeedbackEvent();
				ufe->header.header.event_type = EVENT_UNIT_MOVE;
				ufe->header.header.total_byte_count = sizeof(UnitFeedbackEvent);
				ufe->header.entity_id = 12345;
				ufe->x = 10 * sin(time0->elapsed() * 10.0) + 0;
				ufe->y = 10 * cos(time0->elapsed() * 10.0) + 0;
				DEBUG("Unit feedback event sending: x="<<  ufe->x << ", y=" << ufe->y);

				ufe->theta = 45.0;
				PacketEvent *pe = new PacketEvent(PACKET_EVENT);
				pe->setEvent((Event*)ufe);
				delete ufe;
				pt->addTXPacket(pe);
		

				i++;
			}
		clientsConnection->nm_mutex.unlock();

		//timekeeping
		gs->tick(time0->elapsed() * 1000, prevTime->elapsed() * 1000);
		prevTime->restart();

		boost::this_thread::sleep(boost::posix_time::milliseconds(5));
	}

	std::cout << "Cleaning up server!\n";

	clientsConnection->stop();

	SDLNet_Quit();

	delete clientsConnection;
	delete gs;
	delete ent;
	delete time0;
	delete prevTime;
}
