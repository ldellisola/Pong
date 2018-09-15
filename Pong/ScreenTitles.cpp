#include "ScreenTitles.h"



#define FONT "font.ttf"


ScreenTitles::~ScreenTitles()
{
	delete this->titleScreen;
	delete this->titleScreenBoxes;
	delete this->gameModeScreen;
	delete this->gameModeBoxes;
}

void ScreenTitles::createTitleScreen()
{
	AllegroColorFactory colorF;
	titleScreenBoxes = new BoxArray();
	this->titleScreen = new AllegroLayout(this->displayW, this->displayH, colorF.create("black"),LayoutDrawMode::Slow);
	titleScreenBoxes->addBox(new AllegroWrittenBox(displayW/2 - 200, displayH * 0.25, 400, 200, 50, "Pong!", FONT, colorF.create("white"), TitleTextID));
	this->titleScreen->addBox((*titleScreenBoxes)[TitleTextID]);
	titleScreenBoxes->addBox(new AllegroButton(displayW / 2 - 100,(float) (displayH * 0.75),200,100,"Play",50, FONT,colorF.create("white"),PlayButtonID));
	this->titleScreen->addBox((*titleScreenBoxes)[PlayButtonID]);
	((AllegroButton*)(*titleScreenBoxes)[PlayButtonID])->setBorderColor(colorF.create("white"));
	((AllegroButton*)(*titleScreenBoxes)[PlayButtonID])->setBorderThickness(2);
}

void ScreenTitles::createDifficultyScreen()
{
	AllegroColorFactory colorF;
	difficultyScreenBoxes = new BoxArray();
	this->difficultyScreen = new AllegroLayout(this->displayW, this->displayH, colorF.create("black"), LayoutDrawMode::Slow);
	difficultyScreenBoxes->addBox(new AllegroWrittenBox(displayW/2 - 200,displayH * 0.25,400,200,50,"Select the difficulty:", FONT,colorF.create("white"),DifficultyTextID));
	difficultyScreen->addBox((*difficultyScreenBoxes)[DifficultyTextID]);
	difficultyScreenBoxes->addBox(new AllegroButton((displayW * 0.25) - 100,displayH * 0.75,200,100,"Easy",20, FONT,colorF.create("white"),EasyButtonID));
	((AllegroButton*)(*difficultyScreenBoxes)[EasyButtonID])->setBorderColor(colorF.create("white"));
	((AllegroButton*)(*difficultyScreenBoxes)[EasyButtonID])->setBorderThickness(-2);
	difficultyScreen->addBox((*difficultyScreenBoxes)[EasyButtonID]);
	difficultyScreenBoxes->addBox(new AllegroButton((displayW * 0.5) - 100, displayH * 0.75, 200, 100, "Medium", 20, FONT, colorF.create("white"), MediumButtonID));
	((AllegroButton*)(*difficultyScreenBoxes)[MediumButtonID])->setBorderColor(colorF.create("white"));
	((AllegroButton*)(*difficultyScreenBoxes)[MediumButtonID])->setBorderThickness(-2);
	difficultyScreen->addBox((*difficultyScreenBoxes)[MediumButtonID]);
	difficultyScreenBoxes->addBox(new AllegroButton((displayW * 0.75) - 100, displayH * 0.75, 200, 100, "Hard", 20, FONT, colorF.create("white"), HardButtonID));
	((AllegroButton*)(*difficultyScreenBoxes)[HardButtonID])->setBorderColor(colorF.create("white"));
	((AllegroButton*)(*difficultyScreenBoxes)[HardButtonID])->setBorderThickness(-2);
	difficultyScreen->addBox((*difficultyScreenBoxes)[HardButtonID]);

}

void ScreenTitles::createGameModeScreen()
{
	AllegroColorFactory colorF;
	gameModeScreen = new AllegroLayout(this->displayW, this->displayH, colorF.create("black"), LayoutDrawMode::Slow);
	gameModeBoxes = new BoxArray();

	gameModeBoxes->addBox(new AllegroWrittenBox(displayW / 2 - 400, displayH * 0.25, 800, 200, 50, "Select the game mode:", FONT, colorF.create("white"), GameModeTextID));
	gameModeScreen->addBox((*gameModeBoxes)[GameModeTextID]);
	
	gameModeBoxes->addBox(new AllegroButton((displayW * 0.25) - 300, displayH * 0.75, 600, 100, "Single Player", 50, FONT, colorF.create("white"), SinglePlayerButtonID));
	((AllegroButton*)(*gameModeBoxes)[SinglePlayerButtonID])->setBorderColor(colorF.create("white"));
	((AllegroButton*)(*gameModeBoxes)[SinglePlayerButtonID])->setBorderThickness(-2);
	gameModeScreen->addBox((*gameModeBoxes)[SinglePlayerButtonID]);

	gameModeBoxes->addBox(new AllegroButton((displayW * 0.5) - 300, displayH * 0.75, 600, 100, "MultiPlayer", 50, FONT, colorF.create("white"), MultiPlayerButtonID));
	((AllegroButton*)(*gameModeBoxes)[MultiPlayerButtonID])->setBorderColor(colorF.create("white"));
	((AllegroButton*)(*gameModeBoxes)[MultiPlayerButtonID])->setBorderThickness(-2);
	gameModeScreen->addBox((*gameModeBoxes)[MultiPlayerButtonID]);

	gameModeBoxes->addBox(new AllegroButton((displayW * 0.75) - 300, displayH * 0.75, 600, 100, "No Player", 50, FONT, colorF.create("white"), NoPlaterButtonID));
	((AllegroButton*)(*gameModeBoxes)[NoPlaterButtonID])->setBorderColor(colorF.create("white"));
	((AllegroButton*)(*gameModeBoxes)[NoPlaterButtonID])->setBorderThickness(-2);
	gameModeScreen->addBox((*gameModeBoxes)[NoPlaterButtonID]);

}

int ScreenTitles::runTitleScreen(AllegroEvent ev, AllegroWindow& window)
{
	switch (ev.getType())
	{
	case EventType::DisplayClose:
		return ExitGame;
	case EventType::MouseDown:
		if (((AllegroButton*)(*titleScreenBoxes)[PlayButtonID])->doubleClick(ev.getX(), ev.getY(), ev.getTimestamp()))
			return GameModeSelectionState; // success
		break;
	case EventType::Timer:
		window.update();
		break;
	}
	return TitleScreenState;
}

int ScreenTitles::runDifficultyScreen(AllegroEvent ev, int& difficulty, AllegroWindow& window)
{
	switch (ev.getType())
	{
	case EventType::DisplayClose:
		return ExitGame;//quit
	case EventType::MouseDown:
		if (((AllegroButton*)(*difficultyScreenBoxes)[EasyButtonID])->doubleClick(ev.getX(), ev.getY(), ev.getTimestamp())) {
			difficulty = EasyDifficulty;
			return GameState; // success
		}
		if (((AllegroButton*)(*difficultyScreenBoxes)[MediumButtonID])->doubleClick(ev.getX(), ev.getY(), ev.getTimestamp())) {
			difficulty = MediumDifficulty;
			return GameState; // success
		}
		if (((AllegroButton*)(*difficultyScreenBoxes)[HardButtonID])->doubleClick(ev.getX(), ev.getY(), ev.getTimestamp())) {
			difficulty = HardDifficulty;
			return GameState; // success
		}
		break;
	case EventType::Timer:
		window.update();
		break;
	}
	return DifficultySelectionState;
}

int ScreenTitles::runGameModeScreen(AllegroEvent ev, int & gameMode, AllegroWindow& window)
{
	switch (ev.getType())
	{
	case EventType::DisplayClose:
		return ExitGame;//quit
	case EventType::MouseDown:
		if (((AllegroButton*)(*gameModeBoxes)[SinglePlayerButtonID])->doubleClick(ev.getX(), ev.getY(), ev.getTimestamp())) {
			gameMode = GameModeSinglePlayer;
			return GameState; // success
		}
		if (((AllegroButton*)(*gameModeBoxes)[MultiPlayerButtonID])->doubleClick(ev.getX(), ev.getY(), ev.getTimestamp())) {
			gameMode = GameModeDoublePlayer;
			return GameState; // success
		}
		if (((AllegroButton*)(*gameModeBoxes)[NoPlaterButtonID])->doubleClick(ev.getX(), ev.getY(), ev.getTimestamp())) {
			gameMode = GameModeNoPlayer;
			return GameState; // success
		}
		break;
	case EventType::Timer:
		window.update();
		break;
	}
	return GameModeSelectionState;
}
