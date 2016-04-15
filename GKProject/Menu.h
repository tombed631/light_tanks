#ifndef Menu_hpp
#define Menu_hpp
#endif

#include "Includes.h"
#include "Game.h"
#include "Help.h"
#include "3Dft\TankSelector.h"
/*
 Class to create menu 
*/
class Menu
{
private:
	Event eventHandle; //handle events
	bool isRunningMenu; // is app running? 
	Font font;
	p3d::TankSelector tankSelector;	//tank selector as member to load 3d stuff only once
	const static int optionsNumber = 4; // liczba opcji w menu
	int counter; // licznik do zmiany opcji menu za pomoca klawiatury
public:
	/*Constructor*/
	Menu();
	/*Shows Menu in window */
	void showMenu(RenderWindow &window);
	/*Load font from file*/
	void loadFont();
};