/*
	Server main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>

#include "ClientAccepter.h"
#include "packet.h"

ClientAccepter *nl;

void listen_thread()
{
	try
	{
		nl = new ClientAccepter(20000);
		
		while(1)
		{
			nl->process();
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		}
		
		delete nl;
	}
	catch(const char *e)
	{
		std::cout << e << "\n";
	}
}

int main(int argc, char **argv)
{
	std::cout << "Starting server!\n";
	
	SDLNet_Init();
	
	boost::thread listener(listen_thread);//fork
	
	while(1) 
	{
		if(!nl) continue;
		nl->nm_mutex.lock();// lock the network managers
			for(int i = 0; i < nl->PacketTransporters.size(); i++)
			{
				//process packets
				Packet *p;
				PacketTransporter *nm = nl->PacketTransporters[i];
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
						nl->PacketTransporters[i] = 0; //TODO delete members
						break;
					}
				}
			}
		nl->nm_mutex.unlock();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_Quit();
}
