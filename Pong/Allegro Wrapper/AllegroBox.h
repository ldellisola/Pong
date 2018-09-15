#pragma once

#include <string>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#define DefaultID (0)

enum class BoxType
{
	Box, Button, Toggle, Written, Writable
};


class AllegroBox
{
public:
	// Constructor
	//
	//		- float x:		initial X coordinate.
	//		- float y:		initial Y coordinate.
	//		- float width:	width of the box.
	//		- float height: height of the box.
	//		- BoxType type: Type of the box. It can be a Box, a button, a toggle, a WrittenBox or a WritableBox.
	//		- unsigned int boxID : Unique ID to each box, if the user decides not to assign one, it will be set to DefaultID
	AllegroBox(float x, float y, float width, float height, unsigned int boxID = DefaultID);
	 virtual ~AllegroBox();

	// Draws the bitmap to the actual screen.
	//
	virtual void draw();

	virtual void resize(float width, float height);
	virtual void loadImageBackground(string imagePath);
	virtual void loadImageBackground(ALLEGRO_BITMAP * image);

	// Setters: each function set a given variable of the box
	//
	virtual void setBackgroundColor(ALLEGRO_COLOR color);
	virtual void setBorderColor(ALLEGRO_COLOR color);
	virtual void setBorderThickness(float thickness);
	virtual void setX(float x);
	virtual void setY(float y);
	virtual void setImageAsBackground();
	virtual void setColorAsBackground();
	virtual void setRotationDegree(double degree); // It does not support radians, because fuck radians
	

	// Getters: each function returns a given variable of the box

	virtual ALLEGRO_BITMAP * getBitmap();
	virtual ALLEGRO_COLOR getBorderColor();
	virtual ALLEGRO_COLOR getBackgroundColor();
	virtual float getBorderThickness();
	virtual float getX();
	virtual float getY();
	virtual float getWidth();
	virtual float getHeight();
	virtual unsigned int getID();
	virtual BoxType getType();

	// Overloaded operators.

	bool operator==(AllegroBox&box);
	bool operator!=(AllegroBox&box);

protected:
	// This function is called everytime a change is made in the box to reflect that change on the bitmap
	// it should only be called from within the clases.
	virtual void setUp();
	virtual void setBoxType(BoxType type);
	ALLEGRO_BITMAP * bitmap = nullptr;
	ALLEGRO_BITMAP * imageBackground = nullptr;
	ALLEGRO_COLOR borderColor;
	ALLEGRO_COLOR backgroundColor;
	bool drawImage = false;
	bool foreignImage = false;
	float borderThickness;
	double rotationDegree = 0;
	float x;
	float y;
	float width;
	float height;
	BoxType type;
	// ID given to all boxes and derivated classes. This is useful to identify boxes when you have an array of boxes (Duh).
	// All boxes will have 0 as default ID, if the user decides not to assign one to it.
	unsigned int ID;
};

