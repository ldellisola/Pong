#pragma once
#include "AllegroBox.h"
#include <string>
#include <vector>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

using namespace std;

#define KeyPressedTimeThreshold (0.00001)

enum class KeyboardMode
{
	Numeric, Alphabetic, Alphanumeric 
};

struct AllegroWritableBoxData
{
	KeyboardMode mode;
	float x, y, maxLenght;
	ALLEGRO_FONT * font;
	ALLEGRO_COLOR fontColor;
};


class AllegroWritableBox :public AllegroBox{
public:
	// Constructor: It creates a new font.
	//
	//		- KeyboardMode mode:		the mode of the keyboard. It can be Numeric, Alphanumeric or Alphabetic
	//		- float x:					the initial X coordinate.
	//		- float y:					the initial Y coordinate.
	//		- unsigned int maxLenght:	the max ammount of characters that the box will contain.
	//		- int fontSize:				size of the font.
	//		- const char * fontPath:	the path to the font.
	//		- ALLEGRO_COLOR fontColor:	color of the font.
	AllegroWritableBox(KeyboardMode mode, float x, float y, unsigned int maxLenght, int fontSize, const char * fontPath, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		:AllegroBox(x, y, fontSize* (2 + maxLenght), 3 * fontSize, boxID) {
		this->setBoxType(BoxType::Writable);
		this->maxLenght = maxLenght;
		this->fontColor = fontColor;
		foreingFont = false;
		this->mode = mode;
		this->font = al_load_font(fontPath, -fontSize, 0);
	}

	// Constructor: It takes an existing font.
	//
	//		- KeyboardMode mode:		the mode of the keyboard. It can be Numeric, Alphanumeric or Alphabetic
	//		- float x:					the initial X coordinate.
	//		- float y:					the initial Y coordinate.
	//		- unsigned int maxLenght:	the max ammount of characters that the box will contain.
	//		- ALLEGRO_FONT * font:		pointer to the font
	//		- ALLEGRO_COLOR fontColor:	color of the font.
	AllegroWritableBox(KeyboardMode mode, float x, float y, unsigned int maxLenght, ALLEGRO_FONT * font, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		:AllegroBox(x, y, (maxLenght +2) *al_get_text_width(font, "W"), 3 * al_get_font_line_height(font), boxID) {
		this->setBoxType(BoxType::Writable);
		this->maxLenght = maxLenght;
		this->fontColor = fontColor;
		foreingFont = true;
		this->mode = mode;
		this->font = font;
	}

	// Constructor: It will take an existing font. This is a good option for when you have to create a lot of identical Boxes or you need to 
	//				create a box inside another function and you need all of this information from outside of it.
	//
	//		- AllegroWrittenBoxData& data: a structure with all the data of a box
	AllegroWritableBox(AllegroWritableBoxData& data, unsigned int boxID = DefaultID)
		: AllegroBox(data.x, data.y, (data.maxLenght + 2) *al_get_text_width(data.font, "W"), 3 * al_get_font_line_height(data.font), boxID) {
		this->setBoxType(BoxType::Writable);
		this->maxLenght = data.maxLenght;
		this->fontColor = data.fontColor;
		foreingFont = true;
		this->mode = data.mode;
		this->font = data.font;
	}

	~AllegroWritableBox();

	// It returns the text that the user has typed
	string getText();

	// It takes a keyboard event and uses the key that was pressed. 
	void input(ALLEGRO_KEYBOARD_EVENT ev);

	// It restarts the texts that the user typed
	void clearText();
	
private:
	// It updates the internal bitmap of the box.
	void setUp();
	// If the key is a number, it will add it to the text.
	void addNumber(int num);
	// If the key is a letter, it will add it to the text.
	void addLetter(int let, unsigned int modifiers);

	// If the text is 'backspace' it will delete a key.
	void deleteLetter(int let);

	double timeStamp = 0;

	string text = "";
	KeyboardMode mode;
	unsigned int maxLenght;
	ALLEGRO_COLOR fontColor;
	ALLEGRO_FONT * font = nullptr;
	bool foreingFont = false;
};

