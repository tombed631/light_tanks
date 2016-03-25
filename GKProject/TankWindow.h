#ifndef TankWindow_hpp
#define TankWindow_hpp
#endif
#include "Includes.h"
#include "Menu.h"

/*
Class to create window object
*/
class TankWindow
{

	Menu menu; //object of menu
public:
	/*	Method to render window */
	void renderWindow(int height, int width, string name);

};

