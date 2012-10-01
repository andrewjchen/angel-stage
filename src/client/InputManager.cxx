#include "InputManager.hxx"
#include "Debug.hxx"
#include "ClientGameState.hxx"
#include "Event.hxx"
#include "EventTypes.hxx"
#include "NetworkConnecter.hxx"
#include "Packet.hxx"
#include <stdio.h>

#include "Client.hxx"

InputManager::InputManager(Client* client) {
	ALLEGRO_EVENT_SOURCE * keyboard_source;
	ALLEGRO_EVENT_SOURCE * mouse_source;
	if (   !al_init()
		|| !al_init_image_addon()
		|| !al_init_primitives_addon()
		|| !al_install_keyboard()
		|| !al_install_mouse()
		|| !(keyboard_source = al_get_keyboard_event_source())
		|| !(mouse_source = al_get_mouse_event_source())
		|| !(_event_queue = al_create_event_queue())
		|| !(client->display = al_create_display(client->display_width, client->display_height))
		)
	{
		printf("Cannot initalize Allegro.\n");
	};
	al_set_target_backbuffer(client->display);
	al_register_event_source(_event_queue, keyboard_source);
	al_register_event_source(_event_queue, mouse_source);
	_client = client;
	_selected_units = NULL;
}

InputManager::~InputManager() {
	if (_selected_units) {
		delete _selected_units;
	}
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_primitives_addon();
	al_destroy_display(_client->display);
}

void InputManager::tick(double wall, double delta) {
	al_get_keyboard_state(&_keyboard);
	al_get_mouse_state(&_mouse);
	Position pos = _client->renderer->get_viewpoint();
	if (al_key_down(&_keyboard, ALLEGRO_KEY_DOWN)) {
		_client->renderer->set_viewpoint(pos.get_x(), pos.get_y() + delta / 4.0);
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_UP)) {
		_client->renderer->set_viewpoint(pos.get_x(), pos.get_y() - delta / 4.0);
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_LEFT)) {
		_client->renderer->set_viewpoint(pos.get_x() - delta / 4.0, pos.get_y());
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_RIGHT)) {
		_client->renderer->set_viewpoint(pos.get_x() + delta / 4.0, pos.get_y());
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_S)) {
		DEBUG("S");

		UnitMoveEvent* ume = new UnitMoveEvent();
		ume->header.header.event_type = EVENT_UNIT_MOVE;
		ume->header.header.total_byte_count = sizeof(UnitMoveEvent);
		ume->header.entity_id = 1;

		ume->xGoal = 500;
		ume->yGoal = 500;

		PacketEvent *pe = new PacketEvent();
		pe->setEvent((Event*)ume);

		_client->network_connector->send_packet(pe);
	}
	while (al_get_next_event(_event_queue, &_current_event)) {
		react();
	}
}

void InputManager::react() {
	Position pos = _client->renderer->get_viewpoint();
	switch (_current_event.type) {
		case ALLEGRO_EVENT_KEY_DOWN: {
			switch(_current_event.keyboard.keycode) {
				case ALLEGRO_KEY_SPACE: {
					DEBUG("Space key pressed.\n");
					Event e;
					e.event_type = EVENT_ENTITY_SPAWN;
					e.total_byte_count = sizeof(Event);
					PacketEvent p;
					p.setEvent(&e);
					_client->network_connector->send_packet((Packet*)&p);
					break;
				}
				case ALLEGRO_KEY_U: {
						_client->keep_running = false;
						break;
				}
				case ALLEGRO_KEY_B: {
					Event *e = new Event();
					e->event_type = EVENT_TEST;
					e->total_byte_count = sizeof(Event);
					PacketEvent p;
					p.setEvent(e);
					delete e;
					_client->network_connector->send_packet((Packet*)&p);
					break;
				}
				case (ALLEGRO_KEY_A): {
					PacketPing p;
					p.pingstuff = 0x12345678;
					_client->network_connector->send_packet((Packet*)&p);
					break;
				}

				case (ALLEGRO_KEY_M): { //MERGE
					if(_selected_units && _selected_units->size() > 1){
						//merge unit 0 to unit 1
						UnitMergeEvent* ume = new UnitMergeEvent();
						ume->header.header.event_type = EVENT_UNIT_MERGE;
						ume->header.header.total_byte_count= sizeof(UnitMergeEvent);
						ume->header.entity_id = _selected_units->at(0)->get_id();
						ume->partner = _selected_units->at(1)->get_id();
						PacketEvent *pe = new PacketEvent();
						pe->setEvent((Event*)ume);
						_client->network_connector->send_packet(pe);
						delete pe;
						delete ume;
					}
					break;
				}
				case ALLEGRO_KEY_Q:
					{
						DEBUG("MOUSE_BUTTON_UP!");
						Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
						_mouse_corner_end = gameFromScreen(_client->renderer->get_viewpoint(), screen_pos);
						DEBUG("Start corner: " << _mouse_corner_start.get_x() <<
							  ", " <<_mouse_corner_start.get_y());
						DEBUG("End corner: " << _mouse_corner_end.get_x() <<
							  ", " << _mouse_corner_end.get_y());
						UnitMoveEvent* ume = new UnitMoveEvent();
						ume->header.header.event_type = EVENT_UNIT_MOVE;
						ume->header.header.total_byte_count = sizeof(UnitMoveEvent);
						ume->header.entity_id = 1;

						ume->xGoal = _mouse_corner_end.get_x();
						ume->yGoal = _mouse_corner_end.get_y();

						PacketEvent *pe = new PacketEvent();
						pe->setEvent((Event*)ume);

						_client->network_connector->send_packet(pe);
						break;
					}
				case ALLEGRO_KEY_W:
					{
						DEBUG("MOUSE_BUTTON_UP!");
						Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
						_mouse_corner_end = gameFromScreen(_client->renderer->get_viewpoint(), screen_pos);
						DEBUG("Start corner: " << _mouse_corner_start.get_x() <<
							  ", " <<_mouse_corner_start.get_y());
						DEBUG("End corner: " << _mouse_corner_end.get_x() <<
							  ", " << _mouse_corner_end.get_y());
						UnitMoveEvent* ume = new UnitMoveEvent();
						ume->header.header.event_type = EVENT_UNIT_MOVE;
						ume->header.header.total_byte_count = sizeof(UnitMoveEvent);
						ume->header.entity_id = 2;

						ume->xGoal = _mouse_corner_end.get_x();
						ume->yGoal = _mouse_corner_end.get_y();

						PacketEvent *pe = new PacketEvent();
						pe->setEvent((Event*)ume);

						_client->network_connector->send_packet(pe);
						break;
					}
				case ALLEGRO_KEY_H:
					{
						if(_selected_units && _selected_units->size() > 1){
							//merge unit 0 to unit 1
							std::vector<ClientEntity *>::iterator iter = _selected_units->begin();
							EntityID to_chase = (*iter)->get_id();
							while (iter != _selected_units->end()) {
								UnitChaseEvent *e = new UnitChaseEvent();
								e->header.header.event_type = EVENT_UNIT_CHASE;
								e->header.header.total_byte_count = sizeof(UnitChaseEvent);
								e->header.entity_id = (*iter)->get_id();
								e->target = to_chase;
								PacketEvent p;
								p.setEvent((Event*)e);
								delete e;
								_client->network_connector->send_packet((Packet*)&p);
								++iter;
							}
						}
					}
				break;
			}
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
			switch (_current_event.mouse.button) {
				case 1: {
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					_client->renderer->set_selection_rect_start(gameFromScreen(_client->renderer->get_viewpoint(), screen_pos));
					_mouse_corner_start = gameFromScreen(_client->renderer->get_viewpoint(), screen_pos);
					break;
				}
			}
			break;
		}
		case ALLEGRO_EVENT_MOUSE_AXES: {
			if (al_mouse_button_down(&_mouse, 1)) {
				Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
				_client->renderer->set_selection_rect_end(gameFromScreen(_client->renderer->get_viewpoint(), screen_pos));
				_mouse_corner_end = gameFromScreen(_client->renderer->get_viewpoint(), screen_pos);
			}
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
			switch (_current_event.mouse.button) {
				case 1: {
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					_client->renderer->set_selection_rect_end(gameFromScreen(_client->renderer->get_viewpoint(), screen_pos));
					_client->renderer->set_selection_rect_start(gameFromScreen(_client->renderer->get_viewpoint(), screen_pos));
					_mouse_corner_end = gameFromScreen(_client->renderer->get_viewpoint(), screen_pos);
					select_from_rect();
					break;
				}
				case 2: {
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					Position game_pos = gameFromScreen(_client->renderer->get_viewpoint(), screen_pos);
					if (_selected_units) {
						std::vector<ClientEntity *>::iterator iter = _selected_units->begin();
						while (iter != _selected_units->end()) {
							UnitMoveEvent* ume = new UnitMoveEvent();
							ume->header.header.event_type = EVENT_UNIT_MOVE;
							ume->header.header.total_byte_count = sizeof(UnitMoveEvent);
							ume->header.entity_id = (*iter)->get_id();
							ume->xGoal = game_pos.get_x();
							ume->yGoal = game_pos.get_y();
							send_packet((Event*)ume); delete ume;
							++iter;
						}
					}
					break;
				}

				case 3: {
					UnitSpawnEvent u;
					u.header.event_type = EVENT_ENTITY_SPAWN;
					u.header.total_byte_count = sizeof(UnitSpawnEvent);
					u.x = _current_event.mouse.x;
					u.y = _current_event.mouse.y;
					u.theta = 0;
					u.size = 1.0;

					DEBUG(
						"spawning unit: x= " << u.x <<
						", y=" << u.y );
					 send_packet((Event*)&u);


				}
			}
		}
	}
}

void InputManager::select_from_rect() {
	if (_selected_units) {
		delete _selected_units;
	}
	_selected_units = _client->gamestate->get_entities_in_rect(_mouse_corner_start, _mouse_corner_end);
	DEBUG(_selected_units->size() << " units selected.");
	for(unsigned int i = 0; i < _selected_units->size(); i++){
		DEBUG("_selected unit: id="<< _selected_units->at(i)->get_id());
	}
}


void InputManager::send_packet(Event* e) {
	PacketEvent*pe = new PacketEvent();
	pe->setEvent(e);
	_client->network_connector->send_packet(pe);
	delete pe;
}
