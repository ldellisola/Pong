#include "Pong.h"





Pong::~Pong()
{
}

int Pong::dispatchEvent(AllegroEvent ev, AllegroWindow & window)
{
	switch (ev.getType()) {
	case EventType::DisplayClose:
		return (ExitGame);
	case EventType::KeyDown:
		switch (*gameMode) {
		case GameModeSinglePlayer:
			leftPaddleUserPress(ev.getValue());
			break;
		case GameModeDoublePlayer:
			leftPaddleUserPress(ev.getValue());
			rightPaddleUserPress(ev.getValue());
			break;
		}
		break;
	case EventType::KeyUp:
		switch (*gameMode) {
		case GameModeSinglePlayer:
			leftPaddleUserRelease(ev.getValue());
			break;
		case GameModeDoublePlayer:
			leftPaddleUserRelease(ev.getValue());
			rightPaddleUserRelease(ev.getValue());
			break;
		}
		break;
	case EventType::Timer:
		switch (*gameMode)
		{
		case GameModeSinglePlayer:
			AIPrediction(rightPaddle);
			break;
		case GameModeDoublePlayer:
			break;
		case GameModeNoPlayer:
			AIPrediction(leftPaddle);
			AIPrediction(rightPaddle);
			break;
		}

		puck->update();
		leftPaddle->update();
		rightPaddle->update();

		if (leftPaddle->collision(puck->getX(), puck->getY(), puck->getRadius()))
			puck->bounce();
		else if (rightPaddle->collision(puck->getX(), puck->getY(), puck->getRadius()))
			puck->bounce();

		if (leftPaddle->collisionMissed(puck->getX(), puck->getY(), puck->getRadius())) {
			puck->startOver();
			rightScoreBoard->addPoint();
		}
		else if (rightPaddle->collisionMissed(puck->getX(), puck->getY(), puck->getRadius())) {
			puck->startOver();
			leftScoreBoard->addPoint();
		}

		window.update();

		if (leftScoreBoard->score == MaxScore)
			return LeftWon;
		else if (rightScoreBoard->score == MaxScore)
			return RightWon;
		break;
	}

	return GameState;
}

void Pong::AIPrediction(Paddle * paddle)
{
	((PaddleAI*)paddle)->predictMovement(puck->getX(), puck->getY());

}

void Pong::leftPaddleUserPress(int keycode)
{
	if (keycode == ALLEGRO_KEY_W)
		this->leftPaddle->moveUp();
	else if (keycode == ALLEGRO_KEY_S)
		this->leftPaddle->moveDown();
}

void Pong::rightPaddleUserPress(int keycode)
{
	if (keycode == ALLEGRO_KEY_DOWN)
		rightPaddle->moveDown();
	else if (keycode == ALLEGRO_KEY_UP)
		rightPaddle->moveUp();
}

void Pong::rightPaddleUserRelease(int keycode)
{
	if (keycode == ALLEGRO_KEY_DOWN || keycode == ALLEGRO_KEY_UP)
		rightPaddle->stop();
}

void Pong::leftPaddleUserRelease(int keycode)
{
	if (keycode == ALLEGRO_KEY_S || keycode == ALLEGRO_KEY_W)
		leftPaddle->stop();
}
