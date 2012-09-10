/*
	Server main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>

#include "ClientAccepter.hxx"
#include "Packet.hxx"

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

		
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_Quit();
}
