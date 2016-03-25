
#ifndef _TANK_SELECTOR_
#define _TANK_SELECTOR_

#include <SFML\Window.hpp>
#include "TankTypes.h"


//
//	Provides GUI for tank selecting option in game menu.
//
//	author:	Bart³omiej Ryœ
//	version 1.0
//	
class TankSelector{

public:

	//Default constructor.
	//Note that you need to set thetarget window 
	//before you actually use TankSelector created with default constructor.
	//See setTargetWindow method.
	TankSelector() = default;

	//Creates TankSelector.
	//sf::Window * window		Target window for rendering
	explicit TankSelector(sf::Window & window){
		gameWindow = &window;
	}

	~TankSelector() = default;

	//Sets target window for rendering
	void setTargetWindow(sf::Window & window){
		gameWindow = &window;
	}

	//Starts TankSelector.
	//Returns tank types chose by players.
	PlTankTypes run();

private:

	//Pointer to the target window for rendering
	sf::Window * gameWindow;




};


#endif