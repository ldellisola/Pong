#pragma once
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

#include "AllegroBox.h"

using namespace std;


struct AllegroWrittenBoxData
{
	float x, y, width, height;
	string text;
	ALLEGRO_FONT * font;
	ALLEGRO_COLOR fontColor;
};


class AllegroWrittenBox : public AllegroBox
{
public:
	// Constructor: It takes an existing font to write.
	//
	//		- float X:					initial X coordinate.
	//		- float Y:					initial Y coordinate.
	//		- float width:				width of the box.
	//		- float height:				height of the box.
	//		- string text:				text to be printed.
	//		- ALLEGRO_FONT * font:		font of the text. IT HAS TO BE DESTROYED MANUALLY OUTSIDE OF THE CLASS.
	//		- ALLEGRO_COLOR fontColor:	color of the font.
	AllegroWrittenBox(float x, float y, float width, float height, string text, ALLEGRO_FONT * font, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		: AllegroBox(x, y, width, height,boxID) {
		this->setBoxType(BoxType::Written);
		this->text = text;
		this->font = font;
		this->fontColor = fontColor;
		foreignFont = true;
		this->setUp();
	}

	// Constructor: It will create a new font.
	//
	//		- float X:					initial X coordinate.
	//		- float Y:					initial Y coordinate.
	//		- float width:				width of the box.
	//		- float height:				height of the box.
	//		- int fontSize:				size of the font.
	//		- string text:				text to be printed.
	//		- const char * fontPath:	path to the font. IT will be destroyed after the object.
	//		- ALLEGRO_COLOR fontColor:	color of the font.
	AllegroWrittenBox(float x, float y, float width, float height, int fontSize, string text, const char * fontPath, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		: AllegroBox(x, y, width, height, boxID) {
		this->setBoxType(BoxType::Written);
		this->text = text;
		this->font = al_load_font(fontPath, -fontSize, ALLEGRO_ALIGN_CENTRE);
		this->fontColor = fontColor;
		foreignFont = false;
		this->setUp();
	}

	// Constructor: It takes an existing font to write. It will also create a box the size of the text.
	//
	//		- float X:					initial X coordinate.
	//		- float Y:					initial Y coordinate.
	//		- string text:				text to be printed.
	//		- ALLEGRO_FONT * font:		font of the text. IT HAS TO BE DESTROYED MANUALLY OUTSIDE OF THE CLASS.
	//		- ALLEGRO_COLOR fontColor:	color of the font.
	AllegroWrittenBox(float x_, float y_, string text_, ALLEGRO_FONT * font, ALLEGRO_COLOR fontColor, unsigned int boxID = DefaultID)
		: AllegroBox(x_, y_, al_get_text_width(font,("WW" + text).c_str()), 3 * al_get_font_line_height(font), boxID) {
		this->setBoxType(BoxType::Written);
		this->text = text_;
		this->font = font;
		this->fontColor = fontColor;
		foreignFont = true;
		this->setUp();
	}

	// Constructor: It will take an existing font. This is a good option for when you have to create a lot of identical Boxes or you need to 
	//				create a box inside another function and you need all of this information from outside of it.
	//
	//		- AllegroWrittenBoxData& data: a structure with all the data of a box
	AllegroWrittenBox(AllegroWrittenBoxData& data, unsigned int boxID = DefaultID)
		: AllegroBox(data.x, data.y, data.width, data.height,boxID) {
		this->setBoxType(BoxType::Written);
		this->text = data.text;
		this->font = data.font;
		this->fontColor = data.fontColor;
		foreignFont = true;
		this->setUp();
	}

	~AllegroWrittenBox();

	// It returns a copy of the text in the box.
	string getText() { return text; }

	// It sets the text for the box to print. DO NOT USE THIS WITH THE THIRD CONSTRUCTOR.
	void setText(string text);

protected:

	// It updates the internal bitmap of the box.
	void setUp();
	
	// It tells you if the font of the box was created within the box or outside of it.
	bool foreignFont;

	string text;
	ALLEGRO_COLOR fontColor;
	ALLEGRO_FONT * font;
	
};

