
#include "TankSelector.h"



///Starts TankSelector.
///Returns tank types chose by players.
///Throws GLEWInitError when failed to initialize GLEW
PlTankTypes TankSelector::run(){
	
	//initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw GLEWInitError();
	}

	//stores tank types chose by players (init with any types)
	PlTankTypes playersTanks = { TankType::GREEN_DESTROYER, TankType::RED_FLAMINGO };

	//determines whether main loop is running or not
	bool isRunning = true;

	//contains event that is currently processed
	sf::Event event;


	//____Main__loop_________
	while (isRunning){

		//Check window's events
		while (gameWindow->pollEvent(event)){


			if (event.type == sf::Event::Closed)
				isRunning = false; //exit tank selector
		}

		//display current frame
		draw();

	} //____Main__loop____end.

	
	// prepare context for SFML
	glUseProgram(0);	//set default openGL shader program
	gameWindow->resetGLStates();	//restore SFML's openGL states

	return playersTanks;
}


///Renders current frame to the window
///and displays it on the screen.
void TankSelector::draw() const{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// TO DO

	gameWindow->display();
}