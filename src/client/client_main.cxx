/*
	Client main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>
#include <stdlib.h>
#include <termios.h>

#include "NetworkConnecter.hxx"
#include "Packet.hxx"

NetworkConnecter *nc;

int main(int argc, char **argv)
{
	struct termios initial_settings, new_settings;
	
	tcgetattr(0,&initial_settings);

	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_lflag &= ~ISIG;
	new_settings.c_cc[VMIN] = 0;
	new_settings.c_cc[VTIME] = 0;

	tcsetattr(0, TCSANOW, &new_settings);

	std::cout << "Starting client!\n";
	
	SDLNet_Init();
	
	nc = new NetworkConnecter("localhost", 20000);
	nc->connect();
	
	while(1)
	{
		Packet *p;
		PacketTransporter *nm = nc->network_manager;
		while(nm && ((p = nm->getRXPacket()) != NULL))
		{
			//std::cout << "got a packet!\n";
			switch(p->type)
			{
			case PACKET_PING:
				std::cout << "got a ping reply!\n";
				std::cout << ((PacketPing*)p)->pingstuff << "\n";
				delete p;
				break;
			}
		}
		
		int c = getchar();
		if(c == 'A')
		{
			p = new PacketPing(PACKET_PING);
			((PacketPing*)p)->pingstuff = 0x12345678;
			nm->addTXPacket(p);
		}
		if(c == 'U')
		{
			p = new PacketDisconnect(PACKET_DISCONNECT);
			nm->addTXPacket(p);
			std::cout << "trying to disconnect\n";
			nm->close();
			break;
		}
		
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	//nc->network_manager->read_thread->join();
	//nc->network_manager->write_thread->join();
	
	delete nc->network_manager;
	//somehow this doesn't work
	//delete nc;
	SDLNet_Quit();
	
	tcsetattr(0, TCSANOW, &initial_settings);
}
