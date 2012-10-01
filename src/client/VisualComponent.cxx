#include "VisualComponent.hxx"

VisualComponent::VisualComponent(ClientEntity * entity) : ClientComponent(entity) {
}

void VisualComponent::tick(double wallTime, double deltaT) {
}

void VisualComponent::render(const Position & viewpoint, Client * client) {
}
