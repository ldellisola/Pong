#pragma once
#include "Allegro Wrapper/AllegroLayout.h"
#include "AllegroV2/AllegroFactory.h"
#include "Allegro Wrapper/WrittenBox.h"
#include "Allegro Wrapper/AllegroButton.h"
#include "Allegro Wrapper/AllegroWindow.h"
#include "AllegroEvent.h"
#include "ImportantConstants.h"

#define TitleTextID (1)
#define PlayButtonID (2)

#define DifficultyTextID (0)
#define EasyButtonID (1)
#define MediumButtonID (2)
#define HardButtonID (3)

#define GameModeTextID (0)
#define SinglePlayerButtonID (1)
#define MultiPlayerButtonID (2)
#define NoPlaterButtonID (3)

class ScreenTitles
{
public:
	ScreenTitles(float displayH, float displayW) {
		this->displayH = displayH;
		this->displayW = displayW;
		createTitleScreen();
		createGameModeScreen();
	}
	~ScreenTitles();
	
	int runTitleScreen(AllegroEvent ev, AllegroWindow& window);
	int runDifficultyScreen(AllegroEvent ev, int& difficulty, AllegroWindow& window);
	int runGameModeScreen(AllegroEvent ev, int& gameMode, AllegroWindow& window);

	AllegroLayout * titleScreen, *difficultyScreen, *gameModeScreen;

private:
	void createTitleScreen();
	void createDifficultyScreen();
	void createGameModeScreen();

	BoxArray * titleScreenBoxes, * difficultyScreenBoxes, * gameModeBoxes;
	float displayH, displayW;

	
};

