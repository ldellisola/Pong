#include "AllegroEvent.h"



AllegroEventHandler::AllegroEventHandler(ALLEGRO_EVENT_QUEUE * queue)
{
	this->eventF = new AllegroEventFactory(queue);
}

AllegroEventHandler::~AllegroEventHandler()
{
	if (this->eventF != nullptr)
		delete this->eventF;
}

bool AllegroEventHandler::isThereEvent()
{
	if (this->eventQueue.size() != 0)
		return true;
	else return false;
}

void AllegroEventHandler::getEvent()
{
	this->eventF->getEvent();

	AllegroEvent temp(EventType::Empty, 0 );

	switch (this->eventF->getEventType()) {
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		temp.setType(EventType::DisplayClose);
		break;
	case ALLEGRO_EVENT_KEY_DOWN:
		temp.setType(EventType::KeyDown);
		temp.setValue(eventF->getKeyboardEvent().keycode);
		temp.setTimestamp(eventF->getKeyboardEvent().timestamp);
		break;
	case ALLEGRO_EVENT_KEY_UP:
		temp.setType(EventType::KeyUp);
		temp.setValue(eventF->getKeyboardEvent().keycode);
		temp.setTimestamp(eventF->getKeyboardEvent().timestamp);
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
		temp.setType(EventType::MouseDown);
		temp.setValue(eventF->getMouseEvent().button);
		temp.setCoordinates(eventF->getMouseEvent().x, eventF->getMouseEvent().y);
		temp.setTimestamp(eventF->getMouseEvent().timestamp);
		break;
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		temp.setType(EventType::MouseUp);
		temp.setValue(eventF->getMouseEvent().button);
		temp.setCoordinates(eventF->getMouseEvent().x, eventF->getMouseEvent().y);
		temp.setTimestamp(eventF->getMouseEvent().timestamp);
		break;
	case ALLEGRO_EVENT_TIMER:
		temp.setType(EventType::Timer);
		break;
	}

	if (temp.getType() != EventType::Empty)
		eventQueue.push(temp);

}

AllegroEvent AllegroEventHandler::ObtainEvent()
{
	AllegroEvent temp = this->eventQueue.front();
	this->eventQueue.pop();
	return temp;
}
