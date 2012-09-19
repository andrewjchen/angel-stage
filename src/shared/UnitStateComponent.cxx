#include "UnitStateComponent.hxx"

void UnitStateComponent::feedback(UnitFeedbackEvent * event) {
	_x = event->x;
	_y = event->y;
	_theta = event->theta;
}
