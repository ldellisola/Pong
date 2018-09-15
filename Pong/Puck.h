#pragma once
#include "Allegro Wrapper/AllegroBox.h"
#include "AllegroV2/AllegroFactory.h"

class Puck : public AllegroBox
{
public:
	Puck(float x, float y, float speed, float radius) :
		AllegroBox(x, y, radius * 2, radius * 2) {
		this->initialX = x;
		this->initialY = y;
		this->initialSpeed = speed;
		this->radius = radius;



		this->startOver();

		AllegroColorFactory colorF;
		this->setBackgroundColor(colorF.create("white"));
	}
	void update();
	void startOver();

	float getRadius();
	void bounce();
	~Puck();
private:
	float speed, angle, radius, speedIncrement = 0.2;
	float initialX, initialY, initialSpeed;

};

