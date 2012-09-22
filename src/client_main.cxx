/*
	Client main process
*/

#include <iostream>
#include <boost/thread/thread.hpp>
#include <stdlib.h>
#include <termios.h>

#include "NetworkConnecter.hxx"
#include "Packet.hxx"
#include "MapRenderer.hxx"
#include "GameState.hxx"
#include "Event.hxx"
#include "EventTypes.hxx"
#include "Map.hxx"

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

	if (!al_init() || !al_init_image_addon())
	{
		printf("Cannot initalize Allegro.\n");
		return 1;
	}
	ALLEGRO_DISPLAY * display = al_create_display(800, 600);
	al_set_target_backbuffer(display);
	Map *map = NULL;
	MapRenderer *render = NULL;
	GameState *gs = new GameState();
	
	int xoff = 0, yoff = 0;

	std::cout << "Starting client!\n";
	
	SDLNet_Init();
	
	nc = new NetworkConnecter("localhost", 20000);
	nc->connect();
	
	while(1)
	{
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
				render = new MapRenderer(map);
				delete p;
				break;
			}
		}
		
		int c = getchar();
		if(c == 'A')
		{
			p = new PacketPing(PACKET_PING);
			((PacketPing*)p)->pingstuff = 0x12345678;
			nc->sendPacket(p);
		}
		if(c == 'B')
		{
			Event *e = new Event();
			e->event_type = EVENT_TEST;
			e->total_byte_count = sizeof(Event);
			p = new PacketEvent(PACKET_EVENT);
			((PacketEvent*)p)->setEvent(e);
			delete e;
			nc->sendPacket(p);
		}
		if(c == 'U')
		{
			p = new PacketDisconnect(PACKET_DISCONNECT);
			nc->sendPacket(p);
			std::cout << "trying to disconnect\n";
			nc->disconnect();
			break;
		}
		if(map)
		{
			if(c == 'i')
				if(yoff > 0) yoff--;
			if(c == 'k')
				if(yoff < map->height()) yoff++;
			if(c == 'j')
				if(xoff > 0) xoff--;
			if(c == 'l')
				if(xoff < map->width()) xoff++;
			if(c == ';')
			{
				xoff = map->width() - 10;
				yoff = map->height() - 10;
			}
			if(c == '\'')
				xoff = yoff = 0;
		}
		
		al_clear_to_color(al_map_rgb(0,0,0));
		if(render)
			render->render(xoff, yoff);
		al_flip_display();
		//boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	
	//nc->network_manager->read_thread->join();
	//nc->network_manager->write_thread->join();
	
	//delete nc->packetTransport;
	//somehow this doesn't work
	//delete nc;
	SDLNet_Quit();
	
	al_destroy_display(display);
	if(map)
		delete map;
	if(render)
		delete render;
	delete gs;
	
	tcsetattr(0, TCSANOW, &initial_settings);
}