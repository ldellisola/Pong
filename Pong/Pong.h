#pragma once
#include "Paddle.h"
#include "Puck.h"

#include "Allegro Wrapper/AllegroWindow.h"
#include "AllegroEvent.h"
#include "ScoreBoard.h"
#include "ImportantConstants.h"



#define MaxScore (10)

class Pong
{
public:
	Pong(int * gameMode) { this->gameMode = gameMode; }
	~Pong();
	void addLeftPaddle(Paddle * paddle) { this->leftPaddle = paddle; }
	void addRightPaddle(Paddle * paddle) { this->rightPaddle = paddle; }
	void addLeftScoreBoard(ScoreBoard * scoreboard) { this->leftScoreBoard = scoreboard; }
	void addRightScoreBoard(ScoreBoard * scoreboard) { this->rightScoreBoard = scoreboard; }
	void addPuck(Puck * puck) { this->puck = puck; }

	int dispatchEvent(AllegroEvent ev, AllegroWindow& window);

private:

	void AIPrediction(Paddle * paddle);
	void leftPaddleUserPress(int keycode);
	void rightPaddleUserPress(int keycode);
	void rightPaddleUserRelease(int keycode);
	void leftPaddleUserRelease(int keycode);
	

	Paddle * leftPaddle, *rightPaddle;
	ScoreBoard * leftScoreBoard, *rightScoreBoard;
	Puck * puck;
	int * gameMode;
};

