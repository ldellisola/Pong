#pragma once
#include <queue>

#include "../AllegroV2/AllegroFactory.h"
#include <allegro5/allegro.h>

enum class EventType
{
	KeyDown,KeyUp, MouseDown, MouseUp,DisplayClose,Timer, Empty
};

class AllegroEvent
{
public:
	AllegroEvent(EventType type, int value) {
		this->value = value;
		this->type = type;
		x = 0;
		y = 0;
	}
	EventType getType() { return type; }
	int getValue() { return value; }
	void setType(EventType type) { this->type = type; }
	void setValue(int value) { this->value = value; }
	void setTimestamp(double timestamp) { this->timeStamp = timestamp; }
	void setCoordinates(float x, float y) {
		this->x = x; this->y = y;	}
	float getX() { return x; }
	float getY() { return y; }
	double getTimestamp() { return timeStamp; }
private:
	EventType type;
	int value;
	float x, y;
	double timeStamp;

};

class AllegroEventHandler {
public:
	AllegroEventHandler(ALLEGRO_EVENT_QUEUE * queue);
	~AllegroEventHandler();
	bool isThereEvent();
	void getEvent();

	AllegroEvent ObtainEvent();


private:
	AllegroEventFactory * eventF = nullptr;
	std::queue<AllegroEvent> eventQueue;
	
};

