#include "InputManager.hxx"
#include "Debug.hxx"
#include <stdio.h>

InputManager::InputManager() {
	if(!al_install_keyboard()) {
		DEBUG("!al_install_keyboard");
	}
	_event_queue = al_create_event_queue();
	ALLEGRO_EVENT_SOURCE * keyboard_source = al_get_keyboard_event_source();
	if (!keyboard_source || !_event_queue) {
		DEBUG("!keyboard_source || !_event_queue");
	}
	al_register_event_source(_event_queue, keyboard_source);
}

void InputManager::tick() {
	printf("Ticking!");
	while (al_get_next_event(_event_queue, &_current_event)) {
			printf("Reacting!");
			react();
	}
}

void InputManager::react() {
	if (_current_event.type == ALLEGRO_EVENT_KEY_DOWN) {
		switch(_current_event.keyboard.keycode) {
		case (ALLEGRO_KEY_SPACE):
			printf("Space key pressed.");
		}
	}
}
