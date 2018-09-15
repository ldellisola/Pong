#pragma once

#include "Allegro Wrapper/AllegroBox.h"
#include "AllegroV2/AllegroFactory.h"

class Paddle : public AllegroBox
{
public:
	Paddle(float displayH, float x, float step, float height, float width) :
	AllegroBox(x, (displayH / 2.0) - (height / 2.0),width,height){
		this->displayH = displayH;

		this->step = step;

		AllegroColorFactory colorF;

		this->setBackgroundColor(colorF.create("white"));
	}
	~Paddle();
	void moveUp();
	void moveDown();
	void stop();
	void update();
	bool collision(float otherX, float otherY, float otherRadius);
	bool collisionMissed(float otherX, float otherY, float otherRadius);
protected:
	float step;
	float displayH;
	int direction = 0;
};

class PaddleAI : public Paddle {
public:
	void predictMovement(float otherX, float otherY);
	PaddleAI(float displayH, float x, float step, float height, float width) :
		Paddle(displayH, x, step, height, width) {};
};

