#pragma once
#include <string>

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;

enum class TextLogFlag
{
	Regular, NoClose, Monospace
};


// It creates a window to debug in case you don't want to use the terminal
class AllegroLog
{
public:

	// Constructor:
	//
	//		- string title: the title of the debug window.
	//		- TextLogFlag flag: an optional paramenter that affects the debug window. It can be Regular, NoClose or Monospace.
	AllegroLog(string title, TextLogFlag flag = TextLogFlag::Regular);

	//Destructor
	~AllegroLog();

	// It closes the debug window
	void close();

	// It return the event source
	ALLEGRO_EVENT_SOURCE* getEventSource();

	AllegroLog& operator<< (string text);
	AllegroLog& operator<< (char letter);
	AllegroLog& operator<< (int num);
	AllegroLog& operator<< (float num);
	AllegroLog& operator<< (double num);

private:
	ALLEGRO_TEXTLOG * logWindow = nullptr;
};

