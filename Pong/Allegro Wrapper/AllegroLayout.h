#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

#include "AllegroBox.h"

using namespace std;

enum class LayoutDrawMode
{
	Slow, Mid, Fast
};

struct Drawing
{
	ALLEGRO_BITMAP * bitmap;
	float x, y;
	float scaledHeight, scaledWidth, height, width;

};


/*
	AllegroLayout is a class oriented to UI menus and such.
*/

class AllegroLayout {
public:

	// Constructor:
	//
	//		- float w: width of the display or the area that this layout will represent.
	//		- float h: height of the display or the area that this layout will represent.
	//		- Allegro_Color color: color of the background
	//		- LayoutDrawMode mode: it is how the layout will act. If it is set to fast, it will do a lot less of draw calls, but it may affect AllegroButton
	//							   and WritableBoxes, as well as any change in any allegroBox. If it is set to Mid, it will do less draw calls than the average, but
	//							   it will take slightly more time than Fast, as it will only draw AllegroBoxes again. Slow mode will redraw everything everytime.
	AllegroLayout( float w, float h, ALLEGRO_COLOR color, LayoutDrawMode mode = LayoutDrawMode::Mid);

	// Constructor:
	//
	//		- float w: width of the display or the area that this layout will represent.
	//		- float h: height of the display or the area that this layout will represent.
	//		- Allegro_bitmap/string image: image of the background/ path to the image.
	//		- LayoutDrawMode mode: it is how the layout will act. If it is set to fast, it will do a lot less of draw calls, but it may affect AllegroButton
	//							   and WritableBoxes, as well as any change in any allegroBox. If it is set to Mid, it will do less draw calls than the average, but
	//							   it will take slightly more time than Fast, as it will only draw AllegroBoxes again. Slow mode will redraw everything everytime.
	AllegroLayout(float w, float h, string image, LayoutDrawMode mode = LayoutDrawMode::Mid);
	AllegroLayout(float w, float h, ALLEGRO_BITMAP * image, LayoutDrawMode mode = LayoutDrawMode::Mid);

	// Destructor
	~AllegroLayout();

	// Draws the layout
	void draw();

	void setDrawMode(LayoutDrawMode mode);

	// It adds a bitmap to the window. 
	//
	//		- ALLEGRO_BITMAP * bitmap:	bitmap to be drawn.
	//		- float x:					initial X coordinate.
	//		- float y:					initial Y coordinate.
	//		- float scaledHeight:		new height for the bitmap to be printed in.
	//		- float scaledWidth:		new width for the bitmap to be printed in.
	void addDrawing(ALLEGRO_BITMAP * bitmap, float x, float y, float scaledHeight = 0, float scaledWidth = 0);

	// It removes a bitmap that was being drawn on the window.
	void removeDrawing(ALLEGRO_BITMAP *bitmap);

	// It adds an AllegroBox to the window. 
	void addBox(AllegroBox* box);

	// It removes an AllegroBox that was being drawn on the window
	void removeBox(AllegroBox& box);

	// It moves a given draw to another place.
	void moveDrawing(ALLEGRO_BITMAP *bitmapToMove, float newX, float newY);

	// It sets the color of the display.
	void loadBackground(ALLEGRO_COLOR color);

	// It loads the background of the display
	void loadImageBackground(string image);
	void loadImageBackground(ALLEGRO_BITMAP * image);
	void loadImageBackground(AllegroBox& image);

	// It sets a previusly loaded image as the background of the window
	void setImageAsBackground();

	// It sets a previusly selected color as the background of the window
	void setColorAsBackground();

private:
	void setUp();
	void drawBoxes();
	void drawDrawings();

	float w = 0,  h = 0;

	ALLEGRO_BITMAP * layout = nullptr;
	LayoutDrawMode mode;
	vector<Drawing>drawings;
	vector<AllegroBox *> boxes;
	bool backgroundImage = false;
	bool foreignImage = false;
	ALLEGRO_BITMAP * image = nullptr;
	ALLEGRO_COLOR color;

};

struct BoxArray {
public:
	void addBox(AllegroBox* box);
	void deleteBox(unsigned int ID);
	unsigned int size();
	AllegroBox * operator[](unsigned int ID);
	~BoxArray();

private:
	vector<AllegroBox *> boxes;
};