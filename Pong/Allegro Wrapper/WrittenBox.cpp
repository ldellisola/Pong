#include "WrittenBox.h"







AllegroWrittenBox::~AllegroWrittenBox()
{
	if (this->font && foreignFont == false)
		al_destroy_font(this->font);
}

void AllegroWrittenBox::setText(string text)
{
	this->text = text;
	setUp();
}


void AllegroWrittenBox::setUp()
{
	AllegroBox::setUp();

	ALLEGRO_BITMAP * c = al_get_backbuffer(al_get_current_display());
	al_set_target_bitmap(this->bitmap);

	al_draw_text(this->font, this->fontColor, this->width / 2.0, (this->height / 2.0) - (al_get_font_line_height(this->font)/2.0), ALLEGRO_ALIGN_CENTRE, this->text.c_str());

	al_set_target_bitmap(c);
}
