#include "InputManager.hxx"
#include "Debug.hxx"
#include "ClientGlobals.hxx"
#include "Event.hxx"
#include "EventTypes.hxx"
#include "NetworkConnecter.hxx"
#include "Packet.hxx"
#include <stdio.h>

#include "Client.hxx"

InputManager::InputManager(Client* client, Renderer * renderer, NetworkConnecter * net_connecter) {
	if(!al_install_keyboard()) {
		DEBUG("!al_install_keyboard");
	}
	if(!al_install_mouse()) {
		DEBUG("!al_install_mouse");
	}
	_event_queue = al_create_event_queue();
	ALLEGRO_EVENT_SOURCE * keyboard_source = al_get_keyboard_event_source();
	ALLEGRO_EVENT_SOURCE * mouse_source = al_get_mouse_event_source();
	if (!keyboard_source || !_event_queue || !mouse_source) {
		DEBUG("!keyboard_source || !_event_queue || !mouse_source");
	}
	al_register_event_source(_event_queue, keyboard_source);
	al_register_event_source(_event_queue, mouse_source);
	_renderer = renderer;
	_keep_running = true;
	_net_connecter = net_connecter;
	_client = client;
	_selected_units = NULL;
}

void InputManager::tick(double wall, double delta) {
	al_get_keyboard_state(&_keyboard);
	al_get_mouse_state(&_mouse);
	Position pos = _renderer->getViewpoint();
	if (al_key_down(&_keyboard, ALLEGRO_KEY_DOWN)) {
		_renderer->setViewpoint(pos.getX(), pos.getY() + delta / 4.0);
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_UP)) {
		_renderer->setViewpoint(pos.getX(), pos.getY() - delta / 4.0);
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_LEFT)) {
		_renderer->setViewpoint(pos.getX() - delta / 4.0, pos.getY());
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_RIGHT)) {
		_renderer->setViewpoint(pos.getX() + delta / 4.0, pos.getY());
	}
	if (al_key_down(&_keyboard, ALLEGRO_KEY_S)) {
		DEBUG("S");

		// UnitSplitEvent* ev = new UnitSplitEvent();
		// ev->header.header.event_type = EVENT_UNIT_SPLIT;
		// ev->header.header.total_byte_count = sizeof(UnitSplitEvent);
		// ev->header.entity_id = 4;

		

	}
	while (al_get_next_event(_event_queue, &_current_event)) {
		react();
	}
}

void InputManager::react() {
	Position pos = _renderer->getViewpoint();
	switch (_current_event.type) {
		case ALLEGRO_EVENT_KEY_DOWN: {
			switch(_current_event.keyboard.keycode) {
				case ALLEGRO_KEY_SPACE: {
					printf("Space key pressed.\n");
					break;
				}
				case ALLEGRO_KEY_U: {
						_keep_running = false;
						break;
				}
				case ALLEGRO_KEY_B: {
					Event *e = new Event();
					e->event_type = EVENT_TEST;
					e->total_byte_count = sizeof(Event);
					PacketEvent p;
					p.setEvent(e);
					delete e;
					_net_connecter->sendPacket((Packet*)&p);
				}
					break;
				case (ALLEGRO_KEY_A): {
					PacketPing p;
					p.pingstuff = 0x12345678;
					_net_connecter->sendPacket((Packet*)&p);
				}
				break;
			}
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN: {
			switch (_current_event.mouse.button) {
				case 1: {
					// DEBUG("MOUSE_BUTTON_DOWN!");
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					_renderer->setSelectionRectStart(gameFromScreen(_renderer->getViewpoint(), screen_pos));
					_mouse_corner_start = gameFromScreen(_renderer->getViewpoint(), screen_pos);
					break;
				}
				case 2: {
					DEBUG("MOUSE_BUTTON_DOWN!");
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					_mouse_corner_start = gameFromScreen(_renderer->getViewpoint(), screen_pos);
					break;
				}
			}
			break;
		}
		case ALLEGRO_EVENT_MOUSE_AXES: {
				// DEBUG("MOUSE_MOVED!");
				if (al_mouse_button_down(&_mouse, 1)) {
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					_renderer->setSelectionRectEnd(gameFromScreen(_renderer->getViewpoint(), screen_pos));
					_mouse_corner_end = gameFromScreen(_renderer->getViewpoint(), screen_pos);
					// DEBUG("Start corner: " << _mouse_corner_start.getX() <<
					// 	  ", " <<_mouse_corner_start.getY());
					// DEBUG("End corner: " << _mouse_corner_end.getX() <<
					// 	  ", " << _mouse_corner_end.getY());
				}
			break;
		}
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
			switch (_current_event.mouse.button) {
				case 1: {
					// DEBUG("MOUSE_BUTTON_UP!");
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					_renderer->setSelectionRectEnd(gameFromScreen(_renderer->getViewpoint(), screen_pos));
					_renderer->setSelectionRectStart(gameFromScreen(_renderer->getViewpoint(), screen_pos));
					_mouse_corner_end = gameFromScreen(_renderer->getViewpoint(), screen_pos);
					DEBUG("Start corner: " << _mouse_corner_start.getX() <<
						  ", " <<_mouse_corner_start.getY());
					DEBUG("End corner: " << _mouse_corner_end.getX() <<
						  ", " << _mouse_corner_end.getY());
					select_from_rect();
					break;
				}
				case 2: {
					DEBUG("MOUSE_BUTTON_UP!");
					Position screen_pos(_current_event.mouse.x, _current_event.mouse.y);
					_mouse_corner_end = gameFromScreen(_renderer->getViewpoint(), screen_pos);
					DEBUG("Start corner: " << _mouse_corner_start.getX() <<
						  ", " <<_mouse_corner_start.getY());
					DEBUG("End corner: " << _mouse_corner_end.getX() <<
						  ", " << _mouse_corner_end.getY());
					UnitMoveEvent* ume = new UnitMoveEvent();
					ume->header.header.event_type = EVENT_UNIT_MOVE;
					ume->header.header.total_byte_count = sizeof(UnitMoveEvent);
					ume->header.entity_id = 1;

					ume->xGoal = _mouse_corner_end.getX();
					ume->yGoal = _mouse_corner_end.getY();

					PacketEvent *pe = new PacketEvent();
					pe->setEvent((Event*)ume);

					_client->get_networkconnecter()->sendPacket(pe);
					break;
				}
			}
		}
	}
}

bool InputManager::keep_running() {
	return _keep_running;
}

void InputManager::select_from_rect() {
	if (_selected_units) {
		delete _selected_units;
	}
	_selected_units = _client->get_clientgamestate()->get_entities_in_rect(_mouse_corner_start, _mouse_corner_end);
	DEBUG(_selected_units->size() << " units selected.");
}
