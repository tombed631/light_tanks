
#include "TankSelector.h"



///Starts TankSelector.
///Returns tank types chose by players.
///Throws GLEWInitError when failed to initialize GLEW
PlTankTypes TankSelector::run(){
	
	//initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
#ifdef _DEBUG
		std::cout << "Failed to init GLEW" << std::endl;
		system("pause");
#endif
		throw GLEWInitError();
	}

	//stores tank types chose by players (init with any types)
	PlTankTypes playersTanks = { TankType::GREEN_DESTROYER, TankType::RED_FLAMINGO };

	//determines whether main loop is running or not
	bool isRunning = true;

	//contains event that is currently processed
	sf::Event event;
	//////////////////////////////////////
	shader = new Shader("../Tanks/vertexShader.glsl", "../Tanks/fragmentShader.glsl");
	hero = new Model3D("graphics/Rubik's Cube/Rubik's Cube.obj");
	shader->use();
	/////////////////////////////////////////

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

	delete shader;
	delete hero;
	
	// prepare context for SFML
	glUseProgram(0);	//set default openGL shader program
	gameWindow->resetGLStates();	//restore SFML's openGL states

	return playersTanks;
}


///Renders current frame to the window
///and displays it on the screen.
void TankSelector::draw() const{

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//////////////////////////////////////////////////
	glm::mat4 model, projection, view;
	model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	hero->draw(*shader);
	////////////////////////////////////////////////////
	gameWindow->display();
}