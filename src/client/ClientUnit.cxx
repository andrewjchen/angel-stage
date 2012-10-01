#include "ClientUnit.hxx"

#include "Debug.hxx"

#include <math.h>//bitmap sizeing

ClientUnit::ClientUnit(EntityID id, ClientGameState* gamestate):
	ClientEntity(id, gamestate),
	_pos(0,0) {
	_orientation = 0;
	_size = 1.0;

	_bitmap = al_load_bitmap("res/unit.png");
	if (!_bitmap) {
		DEBUG("Bitmap res/unit.png could not be loaded!\n");
	}
	_half_bitmap_width = ceil((double) al_get_bitmap_width(_bitmap) / 2);
	_half_bitmap_height = ceil((double) al_get_bitmap_height(_bitmap) / 2);


}

ClientUnit::~ClientUnit() {
	al_destroy_bitmap(_bitmap);
}

/************** EVENT REACTION ****************/

void ClientUnit::react(EntityEvent* event) {
	//DEBUG("client unit event recieved");
	switch (event->header.event_type) {
		case EVENT_UNIT_FEEDBACK: {
			UnitFeedbackEvent *ufe = (UnitFeedbackEvent*)(event);
			_pos.setX(ufe->x);
			_pos.setY(ufe->y);
			_orientation = ufe->theta;
			_size = ufe->size;
			//DEBUG("POSITION: x=" << _pos.getX() <<", y="<< _pos.getY());
			break;
		}
		case (EVENT_UNIT_MOVE):{
			// UnitFeedbackEvent *ufe = (UnitFeedbackEvent*)(event);
			// _pos.setX(ufe->x);
			// _pos.setY(ufe->y);
			// _orientation = ufe->theta;
			// _size = ufe->size;
			break;
		}
	}


}

void ClientUnit::tick(double wallTime, double deltaT) {

}



/************ STATE *****************/

Position ClientUnit::get_position(){
	return _pos;
}

void ClientUnit::set_position(Position pos) {
	_pos = pos;
}

double ClientUnit::get_orientation() {
	return _orientation;
}

double ClientUnit::get_size() {
	return _size;
}


void ClientUnit::render(const Position& viewpoint, Client* client){
	// DEBUG("rendering!");


	Position screen_pos = screenFromGame(viewpoint, _pos); 
	double screenX = screen_pos.getX();
	double screenY = screen_pos.getY();
	double scale = 16.0 / 512.0 * _size; 
	if (screenX - _half_bitmap_width < client->display_width &&
		screenY - _half_bitmap_height < client->display_height &&
		screenX + _half_bitmap_width > 0 &&
		screenY + _half_bitmap_width > 0 &&
		_bitmap) {

		al_draw_tinted_scaled_rotated_bitmap(
		_bitmap,
		al_map_rgba(0xFF, 0xFF, 0xFF, 0xD0),
		_half_bitmap_width,
		_half_bitmap_height,
		screenX,
		screenY,
		scale,
		scale,
		-_orientation,
		0);
	}	
}



