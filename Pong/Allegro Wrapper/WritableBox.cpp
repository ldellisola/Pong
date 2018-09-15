#include "WritableBox.h"






AllegroWritableBox::~AllegroWritableBox()
{
	if (font != nullptr && foreingFont == false)
		al_destroy_font(font);
}

string AllegroWritableBox::getText()
{
	return this->text;
}

void AllegroWritableBox::input(ALLEGRO_KEYBOARD_EVENT ev)
{
	int character = ev.keycode;
	if (timeStamp == 0) {
		if (text.length() < maxLenght) {
			switch (mode) {
			case KeyboardMode::Alphabetic:
				addLetter(character, ev.modifiers);
				break;
			case KeyboardMode::Alphanumeric:
				addLetter(character, ev.modifiers);
				addNumber(character);
				break;
			case KeyboardMode::Numeric:
				addNumber(character);
				break;
			}
		}
		deleteLetter(character);
		timeStamp = ev.timestamp;
		this->setUp();
	}
	else if (ev.timestamp - timeStamp >= KeyPressedTimeThreshold)
		timeStamp = 0;
}

void AllegroWritableBox::clearText()
{
	this->text = "";
	this->setUp();
}



void AllegroWritableBox::setUp()
{
	AllegroBox::setUp();
	ALLEGRO_BITMAP * c = al_get_backbuffer(al_get_current_display());
	al_set_target_bitmap(this->bitmap);

	al_draw_text(this->font, this->fontColor, this->width / 2.0, (this->height / 2.0) - (al_get_font_line_height(this->font) / 2.0), ALLEGRO_ALIGN_CENTRE, this->text.c_str());

	al_set_target_bitmap(c);
	
}

void AllegroWritableBox::addNumber(int num)
{
	if (num >= ALLEGRO_KEY_0 && num <= ALLEGRO_KEY_9)
		this->text += '0' + (num -ALLEGRO_KEY_0);
}

void AllegroWritableBox::addLetter(int let, unsigned int modifiers)
{
	char initial;
	if (modifiers & ALLEGRO_KEYMOD_CAPSLOCK || modifiers & ALLEGRO_KEYMOD_SHIFT)
		initial = 'A';
	else
		initial = 'a';

	if (ALLEGRO_KEY_A <= let && let <= ALLEGRO_KEY_Z)
		this->text += initial + (let - ALLEGRO_KEY_A);

}




void AllegroWritableBox::deleteLetter(int let)
{
	if (let == ALLEGRO_KEY_BACKSPACE && text.size()>0)
		text.pop_back();
}
