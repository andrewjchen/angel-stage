#ifndef RENDERABLE_HXX
#define RENDERABLE_HXX

#include "Position.hxx"
#include "Client.hxx"

class Renderable {

public:
	virtual void render(const Position& viewport, Client* client) = 0;
};

#endif 