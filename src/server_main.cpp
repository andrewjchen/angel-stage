/*
	Server main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>

#include "network_listen.h"
#include "packet.h"

NetworkListener *nl;

void listen_thread()
{
	try
	{
		nl = new NetworkListener(20000);
		
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
		nl->nm_mutex.lock();
			for(int i = 0; i < nl->network_managers.size(); i++)
			{
				//process packets
				Packet *p;
				NetworkManager *nm = nl->network_managers[i];
				if(nm == 0) continue;
				while(nm && ((p = nm->getRXPacket()) != NULL))
				{
					//std::cout << "got a packet!\n";
					switch(p->type)
					{
					case PACKET_PING:
						std::cout << "got a ping request!\n";
						nm->addTXPacket(p);
						break;
					case PACKET_DISCONNECT:
						std::cout << "got a disconnect packet!\n";
						nm->close();
						delete nm;
						delete p;
						nm = 0;
						nl->network_managers[i] = 0;
						break;
					}
				}
			}
		nl->nm_mutex.unlock();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_Quit();
}
