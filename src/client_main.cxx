/*
	Client main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>
#include <stdlib.h>

#include "NetworkConnecter.hxx"
#include "Packet.hxx"
#include "MapRenderer.hxx"
#include "ClientGameState.hxx"
#include "Event.hxx"
#include "EventTypes.hxx"
#include "Map.hxx"
#include "RenderSetup.hxx"
#include "ClientGlobalsImport.hxx"
#include "Renderer.hxx"
#include "InputManager.hxx"


int main(int argc, char **argv)
{
	if (!setup_rendering()) {
		return 1;
	}

	Map *map = NULL;
	Renderer *renderer = new Renderer();
	ClientGameState *gs = new ClientGameState(renderer);

	std::cout << "Starting client!\n";

	SDLNet_Init();

	NetworkConnecter * nc = new NetworkConnecter("localhost", 20000);
	nc->connect();

	InputManager * input = new InputManager(renderer, nc);
	while(input->keep_running())
	{
		input->tick();
		Packet *p;
		while((p = nc->getPacket()) != NULL)
		{
			//std::cout << "got a packet!\n";
			switch(p->type)
			{
			case PACKET_PING:
				std::cout << "got a ping reply!\n";
				std::cout << ((PacketPing*)p)->pingstuff << "\n";
				delete p;
				break;
			case PACKET_EVENT:
				std::cout << "got an event!\n";
				gs->react(((PacketEvent*)p)->getEvent());
				delete p;
				break;
			case PACKET_MAP:
				std::cout << "got map data!\n";
				map = new Map(((PacketMap*)p)->size);
				// render = new MapRenderer(map);
				renderer->addMap(map);
				delete p;
				break;
			}
		}

		renderer->render();
	}
	Packet * p = new PacketDisconnect(PACKET_DISCONNECT);
	nc->sendPacket(p);
	std::cout << "trying to disconnect\n";
	nc->disconnect();

	delete nc;
	SDLNet_Quit();
	al_destroy_display(display);
	if(map)
		delete map;
	delete renderer;
	delete gs;

}
