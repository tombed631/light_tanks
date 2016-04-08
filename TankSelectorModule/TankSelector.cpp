
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
	///////////////////TEMP_CONTENT_BEGIN///////////////////
	shader = new Shader("../TankSelectorModule/vertexShader.glsl", "../TankSelectorModule/fragmentShader.glsl");
	//hero = new Model3D("../../graphics/GM_Allison_M551_Sheridan_Cavalera_Light_Tank/GM Allison M551 'Sheridan' 'Cavalera Light Tank'.obj");
	//hero = new Model3D("../../graphics/hero/nanosuit.obj");
	hero = new Model3D("../../graphics/Rubik's Cube/Rubik's Cube.obj");
	shader->use();
	glEnable(GL_DEPTH_TEST);
	camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	arcball = new ArcBall(gameWindow->getSize().x, gameWindow->getSize().y);
	model_m = glm::scale(model_m, glm::vec3(0.005f, 0.005f, 0.005f));
	///////////////////TEMP_CONTENT_END//////////////////////

	//____Main__loop_________
	while (isRunning){

		//Check window's events
		while (gameWindow->pollEvent(event)){

			if ((event.type = sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left)) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*gameWindow);
				arcball->enable(mousePosition.x, mousePosition.y);
			}else if ((event.type = sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left)) {
				arcball->disable();
			}else if (event.type == sf::Event::Closed)
				isRunning = false; //exit tank selector
		}


		///////////////////TEMP_CONTENT_BEGIN///////////////////
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (arcball->isEnabled()) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*gameWindow);
				arcball->drag(mousePosition.x, mousePosition.y);
			}
			else {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*gameWindow);
				arcball->enable(mousePosition.x, mousePosition.y);
			}
		}
		else {
			arcball->disable();
		}
		///////////////////TEMP_CONTENT_END//////////////////////
		
		

		//display current frame
		draw();

	} //____Main__loop____end.

	///////////////////TEMP_CONTENT_BEGIN///////////////////
	delete shader;
	delete hero;
	delete camera;
	///////////////////TEMP_CONTENT_END//////////////////////

	
	// prepare context for SFML
	glUseProgram(0);	//set default openGL shader program
	gameWindow->resetGLStates();	//restore SFML's openGL states

	return playersTanks;
}


///Renders current frame to the window
///and displays it on the screen.
void TankSelector::draw(){

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///////////////////TEMP_CONTENT_BEGIN///////////////////
	glm::mat4 projection, view;
	view = camera->getViewMatrix();
	model_m = arcball->getUpdatedModelMatrix(model_m);
	GLfloat width = gameWindow->getSize().x, height = gameWindow->getSize().y;
	projection = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model_m));
	hero->draw(*shader);
	///////////////////TEMP_CONTENT_END//////////////////////
	gameWindow->display();
}