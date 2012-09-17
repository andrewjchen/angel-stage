#include <cstdio>
#include "Entity.hxx"

EntityID Entity::get_id() const {
	return _id;
}

void Entity::react(Event * event) {
	printf("Entity at %p received event!\n", this);
	/* TODO: Do things. */
}
