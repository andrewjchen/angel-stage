#include "InputManager.hxx"
#include "Debug.hxx"
#include "ClientGlobals.hxx"
#include "Event.hxx"
#include "EventTypes.hxx"
#include "NetworkConnecter.hxx"
#include "Packet.hxx"
#include <stdio.h>

InputManager::InputManager(Renderer * renderer, NetworkConnecter * net_connecter) {
	if(!al_install_keyboard()) {
		DEBUG("!al_install_keyboard");
	}
	_event_queue = al_create_event_queue();
	ALLEGRO_EVENT_SOURCE * keyboard_source = al_get_keyboard_event_source();
	if (!keyboard_source || !_event_queue) {
		DEBUG("!keyboard_source || !_event_queue");
	}
	al_register_event_source(_event_queue, keyboard_source);
	_renderer = renderer;
	_keep_running = true;
	_net_connecter = net_connecter;
}

void InputManager::tick(double wall, double delta) {
	while (al_get_next_event(_event_queue, &_current_event)) {
		react();
	}
}

void InputManager::react() {
	Position pos = _renderer->getViewpoint();
	if (_current_event.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch(_current_event.keyboard.keycode) {
		case (ALLEGRO_KEY_SPACE):
			printf("Space key pressed.\n");
			break;
		case (ALLEGRO_KEY_UP):
			_renderer->setViewpoint(pos.getX(), pos.getY() + 1);
			break;
		case (ALLEGRO_KEY_DOWN):
			_renderer->setViewpoint(pos.getX(), pos.getY() - 1);
			break;
		case (ALLEGRO_KEY_LEFT):
			_renderer->setViewpoint(pos.getX() - 1, pos.getY());
			break;
		case (ALLEGRO_KEY_RIGHT):
			_renderer->setViewpoint(pos.getX() + 1, pos.getY());
			break;
		case (ALLEGRO_KEY_U):
			_keep_running = false;
			break;
		case (ALLEGRO_KEY_B): {
			Event *e = new Event();
			e->event_type = EVENT_TEST;
			e->total_byte_count = sizeof(Event);
			Packet * p = new PacketEvent(PACKET_EVENT);
			((PacketEvent*)p)->setEvent(e);
			delete e;
			_net_connecter->sendPacket(p);
		}
		case (ALLEGRO_KEY_A): {
			Packet * p = new PacketPing(PACKET_PING);
			((PacketPing*)p)->pingstuff = 0x12345678;
			_net_connecter->sendPacket(p);
		}
		}
	}
}

bool InputManager::keep_running() {
	return _keep_running;
}
