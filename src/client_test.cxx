#include "Debug.hxx"
#include "NetworkConnecter.hxx"
#include "Timer.hxx"
#include <map>
#include "Event.hxx"
#include "EventTypes.hxx"
#include "Ids.hxx"

int main(int argc, char *argv[]) {

    DEBUG("client test");

    NetworkConnecter conn("127.0.0.1", 20000);
    conn.start();


    Timer timer;


    //std::map<int, bool>


    bool running = true;
    while(running) {
        timer.reset_delta();

        /********* PACKET READ  ************/
        std::list<Packet *>* packets = conn.get_packet(100);
        std::list<Packet *>::iterator i = packets->begin();
        while(i != packets->end()) {
            //std::cout << "got a packet!\n";
            Packet *p = *i;
            switch(p->type) {
                case PACKET_PING: {
                    //DEBUG("got a ping reply!");
                    //DEBUG(((PacketPing*)p)->pingstuff);
                    delete p;
                    break;
                }
                case PACKET_EVENT: {
                    //DEBUG("got an event!");
                    //_gamestate->react(((PacketEvent*)p)->getEvent());
                    Event *event = ((PacketEvent *) p)->getEvent();
                    if(is_entity_event(event)) {
                        // EntityEvent* eevent = ((EntityEvent*)event);
                        // EntityID id = ((EntityEvent*) event)->entity_id;

                        //DEBUG("Entity id=" << id);

                    } else if (is_global_event(event)) {

                        switch (event->event_type) {
                            case EVENT_ENTITY_SPAWN:
                                DEBUG("spawn event");
                                break;
                            case EVENT_ENTITY_DIE:
                                DEBUG("die event");
                                break;
                        }

                    }
                    delete p;
                    break;
                }
                case PACKET_MAP: {
                    //DEBUG("got map data!");
                    //_renderer->add_map(Map::load(((PacketMap*)p)->getStuff()));
                    delete p;
                    break;
                }
            }
            i++;
        }

        /***************** COMMAND SEND IN SEQUENCE ********/



        //DEBUG("Timer: wall=" << timer.wall() << ", delta=" << timer.delta());


    }



    return 0;

}
