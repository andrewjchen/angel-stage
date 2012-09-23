#include "InputManager.hxx"
#include "Debug.hxx"
#include "ClientGlobalsImport.hxx"
#include <stdio.h>

InputManager::InputManager(Renderer * renderer) {
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
}

void InputManager::tick() {
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
		}
	}
}

bool InputManager::keep_running() {
	return _keep_running;
}
