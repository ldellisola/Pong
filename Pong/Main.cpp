#include "AllegroV2/AllegroClassV2.h"
#include "Allegro Wrapper/AllegroWindow.h"
#include "Allegro Wrapper/AllegroLayout.h"

#include "Puck.h"
#include "ScoreBoard.h"
#include "Paddle.h"

#include "ScreenTitles.h"

#include "Pong.h"
#include "ImportantConstants.h"
#include "AllegroEvent.h"


#define PuckSpeed (30)
#define PaddleStep (20)

void setAllegroForGame(AllegroClassV2 &allegro, AllegroWindow& window);
void setAllegroForMenu(AllegroClassV2 &allegro);


int main(void) {

	AllegroClassV2 allegro(Allegro::InitMode::Full, Allegro::NoValue, Allegro::NoValue, 60);
	AllegroEventFactory eventF(allegro.getEventQueue());
	AllegroColorFactory colorF;

	AllegroWindow window(DisplayW, DisplayH, allegro.getEventQueue(), "Pong!");
	window.open();

	AllegroLayout gameLayout(window.getWidth(), window.getHeight(), colorF.create("black"), LayoutDrawMode::Slow);

	ScreenTitles screenTitle(DisplayH, DisplayW);


	Puck * puck = new Puck((float)window.getWidth() / 2.0 , (float)window.getHeight() / 2.0, PuckSpeed, 25);

	Paddle * paddleLeft = nullptr;
	Paddle * paddleRight = nullptr;

	ScoreBoard scoreBoardLeft(window.getWidth()*(0.25), 10, 200, 200, "font.ttf", colorF.create("white"),70);
	ScoreBoard scoreBoardRight(window.getWidth()*(0.75), 10, 200, 200, "font.ttf", colorF.create("white"),70);

	gameLayout.addBox(puck);
	gameLayout.addBox(&scoreBoardLeft);
	gameLayout.addBox(&scoreBoardRight);

	int retCode = TitleScreenState, gameMode;


	Pong pong(&gameMode);
	pong.addPuck(puck);
	pong.addLeftScoreBoard(&scoreBoardLeft);
	pong.addRightScoreBoard(&scoreBoardRight);

	AllegroEventHandler eventHandler(allegro.getEventQueue());
	window.insertLayout(*screenTitle.titleScreen);
	

	do{
		eventHandler.getEvent();
		if (eventHandler.isThereEvent()) {
			switch (retCode) {
			case TitleScreenState:
				retCode = screenTitle.runTitleScreen(eventHandler.ObtainEvent(), window);

				if (retCode == GameModeSelectionState) 
					window.insertLayout(*screenTitle.gameModeScreen);
				break;
			case GameModeSelectionState:

				retCode = screenTitle.runGameModeScreen(eventHandler.ObtainEvent(),gameMode, window);
				if (retCode == GameState) {
					switch (gameMode) {
					case GameModeSinglePlayer:
						paddleLeft = new Paddle((float)window.getHeight(), 10, PaddleStep, 300, 30);
						paddleRight = new PaddleAI((float)window.getHeight(), 2000 - 50, PaddleStep, 300, 30);
						break;
					case GameModeDoublePlayer:
						paddleLeft = new Paddle((float)window.getHeight(), 10, PaddleStep, 300, 30);
						paddleRight = new Paddle((float)window.getHeight(), 2000 - 50, PaddleStep, 300, 30);
						break;
					case GameModeNoPlayer:
						paddleLeft = new PaddleAI((float)window.getHeight(), 10, PaddleStep, 300, 30);
						paddleRight = new PaddleAI((float)window.getHeight(), 2000 - 50, PaddleStep, 300, 30);

					}

					gameLayout.addBox(paddleLeft);
					gameLayout.addBox(paddleRight);
					pong.addLeftPaddle(paddleLeft);
					pong.addRightPaddle(paddleRight);
					window.insertLayout(gameLayout);
					setAllegroForGame(allegro,window);
				}

				break;
			case GameState:
				if (eventHandler.isThereEvent())
					int a = 0;
				retCode = pong.dispatchEvent(eventHandler.ObtainEvent(), window);
				break;
			}
		}
	} while (retCode != ExitGame);


	delete paddleLeft;
	delete paddleRight;
	delete puck;
	
}


void setAllegroForGame(AllegroClassV2 &allegro, AllegroWindow& window) {
	//allegro.uninstallMouseAddon();
	allegro.uninstallVideoAddon();
}

void setAllegroForMenu(AllegroClassV2 & allegro)
{
	//allegro.uninstallKeyboardAddon();
	allegro.initMouseAddon();


}


