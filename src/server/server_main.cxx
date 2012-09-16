/*
	Server main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>

#include "ClientsConnection.hxx"
#include "Packet.hxx"

ClientsConnection * clientsConnection;

int main(int argc, char **argv)
{
	std::cout << "Starting server!\n";
	
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
						nm->close(); //logic
						delete nm;
						delete p;
						nm = 0;
						clientsConnection->packetTransporters[i] = 0; //TODO delete members
						break;
					}
				}
			}
		clientsConnection->nm_mutex.unlock();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_Quit();
}
