#include "NetClients.hxx"


NetClients::NetClients(uint16_t port): clientAccepter(port){

}

NetClients::~NetClients(){

}

void NetClients::initialize(){
	clientAccepter.start();
}

void NetClients::tick(){
	if(clientAccepter){
		clientAccepter->nm_mutex.lock();// lock the network managers
		for(int i = 0; i < clientAccepter->packetTransporters.size(); i++)
		{
			//process packets
			Packet *p;
			PacketTransporter *nm = clientAccepter->packetTransporters[i];
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
					clientAccepter->packetTransporters[i] = 0; //TODO delete members
					break;
				}
			}
		}
		clientAccepter->nm_mutex.lock();
	}

}

void NetClients::sendGameState(GameState state){
	
}