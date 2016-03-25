#ifndef Menu_hpp
#define Menu_hpp
#endif

#include "Includes.h"
/*
 Class to create menu 
*/
class Menu
{
private:
	Event eventHandle; //handle events
	bool isRunning; // is app running? 
	Font font;
	const static int ilosc_opcji = 3;
	int counter; // licznik do zmiany opcji menu za pomoca klawiatury
public:
	/*Constructor*/
	Menu();
	/*Shows Menu in window */
	void showMenu(RenderWindow &window);
	/*Load font from file*/
	void loadFont();
};