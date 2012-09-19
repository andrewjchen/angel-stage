#include "Server.hxx"
#include <SDL/SDL.h>

// Server& Server::getInstance() {
// 	static Server instance;
// 	return instance;
// }

void Server::run() {
	running = true;
	// srand(unsigned(time(0)));
	while(running) {
		// phys.tick();
	// 	net.update();
		SDL_Delay(1);
	}
}
