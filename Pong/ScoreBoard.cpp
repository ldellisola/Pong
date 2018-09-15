#include "ScoreBoard.h"



ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::addPoint()
{
	this->score++;
	update();
}

void ScoreBoard::resetScore()
{
	this->score = 0;
	update();
}

void ScoreBoard::update()
{
	this->setText(to_string(this->score));
}
