/*
	Server main process
*/

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <boost/thread/thread.hpp>
#include <signal.h>

#include "ClientsConnection.hxx"
#include "Packet.hxx"
#include "ServerGameState.hxx"
#include "ServerUnitStateComponent.hxx"
#include "Debug.hxx"

#include <math.h>
#include "Server.hxx"

Server* server;

void sigint_handler(int sig) {
	server->set_running(false);
}

int main(int argc, char **argv) {
	signal(SIGINT, sigint_handler);
	DEBUG("Starting server!");
	server = new Server();
	server->run();
	delete server;
}
