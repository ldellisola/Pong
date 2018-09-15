#include "Paddle.h"
#include <cmath>



Paddle::~Paddle()
{
}

void Paddle::moveUp()
{
	if (this->y >0)
		this->direction = -1;
	else
		this->direction = 0;
}

void Paddle::moveDown()
{
	if ((this->y + this->height )< this->displayH)
		this->direction = 1;
	else
		this->direction = 0;
}

void Paddle::stop()
{
	direction = 0;
}

void Paddle::update()
{
	if ((this->y + direction * this->step) >= 0 && (this->y + this->height + direction * this->step) <= this->displayH) {
		this->y += direction * (this->step);
	}
	
}

bool Paddle::collision(float otherX, float otherY, float otherRadius)
{
	if (this->x <= (otherX + otherRadius * 2) && (this->x + this->width) >= otherX)
		if ((this->y + this->height >= otherY) && (this->y) <= (otherY + otherRadius *2))
			return true;
	return false;
}

bool Paddle::collisionMissed(float otherX, float otherY, float otherRadius)
{
	if (this->x <= (otherX + otherRadius * 2) && (this->x + this->width) >= otherX)
		if ((this->y + this->height < otherY) || (this->y) > (otherY + otherRadius * 2))
			return true;
	return false;
}


void PaddleAI::predictMovement(float otherX, float otherY)
{
	if ( (x-1000 >0)? otherX > 1000: otherX <1000) {
		if (otherY > this->y + this->height / 2.0)
			this->moveDown();
		else if (otherY < this->y + this->height / 2.0)
			this->moveUp();
	}
}
