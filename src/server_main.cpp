/*
	Server main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>

#include "network_listen.h"

void listen_thread()
{
	try
	{
		NetworkListener *nl = new NetworkListener(20000);
		
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
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	SDLNet_Quit();
}
