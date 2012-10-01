#include "Entity.hxx"

Entity::Entity(EntityID id): _id(id) {

}

Entity::~Entity() {

}

EntityID Entity::get_id() {
	return _id;
}

void Entity::react(EntityEvent* event){
	
}