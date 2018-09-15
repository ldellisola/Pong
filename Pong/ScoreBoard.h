#pragma once
#include "Allegro Wrapper/WrittenBox.h"

class ScoreBoard :
	public AllegroWrittenBox
{
public:
	ScoreBoard(float x,float y,float width, float height,string font, ALLEGRO_COLOR fontColor, unsigned int fontSize):
		AllegroWrittenBox(x,y,width,height,fontSize,"0",font.c_str(),fontColor){
		resetScore();
	}
	~ScoreBoard();
	void addPoint();
	void resetScore();
	void update();
	unsigned int score;
};

