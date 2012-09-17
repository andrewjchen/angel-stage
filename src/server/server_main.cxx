/*
	Server main process
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <boost/thread/thread.hpp>

#include "ClientsConnection.hxx"
#include "Packet.hxx"
#include "GameState.hxx"

ClientsConnection * clientsConnection;

int main(int argc, char **argv)
{
	std::cout << "Starting server!\n";
	
	GameState *gs = new GameState();
	
	SDLNet_Init();

	clientsConnection = new ClientsConnection(20000);
	clientsConnection->start();
	
	
	while(1) 
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
						delete nm;
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
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_Quit();
	
	delete gs;
}
