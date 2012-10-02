/*
	Client main process
*/

#include "Client.hxx"
#include "Debug.hxx"
#include "Renderer.hxx"
#include "InputManager.hxx"
#include "Timer.hxx"


int main(int argc, char **argv) {

    Client client;
    client.display_width = 800;
    client.display_height = 600;
    client.display = NULL;
    client.keep_running = true;
    client.input_manager = new InputManager(&client);
    client.renderer = new Renderer(&client);
    client.gamestate = new ClientGameState(&client);
    client.network_connector = new NetworkConnecter("127.0.0.1", 20000);
    client.network_connector->start();

    Timer timer;
    while(client.keep_running) {
        timer.reset_delta();
        std::list<Packet *> * packets = client.network_connector->get_packet(100);
        std::list<Packet *>::iterator i = packets->begin();
        while(i != packets->end()) {
            //std::cout << "got a packet!\n";
            Packet *p = *i;
            switch(p->type) {
                case PACKET_PING:
                    //DEBUG("got a ping reply!");
                    //DEBUG(((PacketPing*)p)->pingstuff);
                    delete p;
                    break;
                case PACKET_EVENT:
                    // DEBUG("got an event!");
                    client.gamestate->react(((PacketEvent *)p)->getEvent());
                    delete p;
                    break;
                case PACKET_MAP:
                    // DEBUG("got map data!");
                    client.renderer->add_map(Map::load(((PacketMap *)p)->getStuff()));
                    delete p;
                    break;
                default:
                    DEBUG("BAD DEFAULT!!!");
            }
            i++;
        }
        client.input_manager->tick(timer.wall(), timer.delta());
        client.renderer->render();
    }
    PacketDisconnect p;
    client.network_connector->send_packet((Packet *)&p);
    DEBUG("trying to disconnect");
    client.network_connector->disconnect();

    delete client.renderer;
    delete client.network_connector;
    delete client.gamestate;
    delete client.input_manager;
}
