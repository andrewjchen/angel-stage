/*
	Server main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>

#include "ClientAccepter.h"
#include "packet.h"

ClientAccepter * clientAccepter;

int main(int argc, char **argv)
{
	std::cout << "Starting server!\n";
	
	SDLNet_Init();

	clientAccepter = new ClientAccepter(20000);
	clientAccepter->start();
	
	
	while(1) 
	{
		if(!clientAccepter) continue;//if null, don't act

		clientAccepter->nm_mutex.lock();// lock the network managers
			for(int i = 0; i < clientAccepter->packetTransporters.size(); i++)
			{
				//process packets
				Packet *p;
				PacketTransporter *nm = clientAccepter->packetTransporters[i];
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
						nm->close(); //logic
						delete nm;
						delete p;
						nm = 0;
						clientAccepter->packetTransporters[i] = 0; //TODO delete members
						break;
					}
				}
			}
		clientAccepter->nm_mutex.lock();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_Quit();
}
