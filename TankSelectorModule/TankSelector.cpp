
#include "TankSelector.h"

//Starts TankSelector.
//Returns tank types chose by players.
PlTankTypes TankSelector::run(){
	
	//stores tank types chose by players (init with any types)
	PlTankTypes playersTanks = { TankType::GREEN_DESTROYER, TankType::RED_FLAMINGO };

	//determines whether main loop is running or not
	bool isRunning = true;

	//contains event that is currently processed
	sf::Event event;


	//Main loop
	while (isRunning){

		//Check window's events
		while (gameWindow->pollEvent(event)){


			if (event.type == sf::Event::Closed)
				isRunning = false; //exit tank selector
		}
	}

	return playersTanks;
}