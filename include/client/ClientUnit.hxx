#ifndef _CLIENT_UNIT_HXX_
#define _CLIENT_UNIT_HXX_

#include "ClientEntity.hxx"//super
#include "Renderable.hxx" //super
#include "Position.hxx"//pose
#include "Client.hxx"//render

class ClientUnit : public ClientEntity, public Renderable{

public:
	ClientUnit(EntityID , ClientGameState* gamestate);
	virtual ~ClientUnit();
	void react(EntityEvent * event);
	virtual void tick(double wallTime, double deltaT);

	//STATE
	Position get_position();
	void set_position(Position pos);
	double get_orientation();
	double get_size();
	void set_size(double size);

	//RENDERING
	virtual void render(const Position& viewpoint, Client* client);

protected:

private:

	/************ STATE ******/

	//pose
	Position _pos;
	double _orientation;

	//attributes
	double _size;

	/********* RENDER ********/
	int32_t _half_bitmap_width;
	int32_t _half_bitmap_height;
	ALLEGRO_BITMAP * _bitmap;


};

#endif /* _ENTITY_HXX_ */
