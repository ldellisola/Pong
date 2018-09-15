#include "Puck.h"
#include <math.h>
#include <random>


const float Pi = 4. * atan(1.);


void Puck::update()
{
	if (this->y <= 0 || this->y + 2 *this->radius >= 1000)
		this->angle = -this->angle;


	this->x += this->speed * cosf(this->angle);
	this->y += this->speed * sinf(this->angle);

}

void Puck::startOver()
{
	std::random_device rand;

	float rndm = rand() % 360;

	while ( ( rndm > 70 && rndm < 110 ) || (rndm >  250 && rndm < 290))
		rndm = rand() % 360;

	this->x = initialX;
	this->y = initialY;
	this->speed = initialSpeed;
	this->angle = rndm * Pi / 180.0;
}





float Puck::getRadius()
{
	return radius;
}

void Puck::bounce()
{
	this->angle = Pi - this->angle;
	this->speed += this->speedIncrement;
}



Puck::~Puck()
{
}

