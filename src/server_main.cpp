/*
	Server main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>

#include "network_listen.h"

int main(int argc, char **argv)
{
	std::cout << "Starting server!\n";
	
	SDLNet_Init();
	NetworkListener *nl = new NetworkListener(20000);
	
	while(1)
	{
		nl->process();
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	delete nl;
	SDLNet_Quit();
}
