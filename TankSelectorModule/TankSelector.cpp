
#include "TankSelector.h"



///Starts TankSelector.
///Returns tank types chose by players.
///Throws GLEWInitError when failed to initialize GLEW
PlTankTypes TankSelector::run(){
	
	//stores tank types chose by players (init with any types)
	PlTankTypes playersTanks = { TankType::GREEN_DESTROYER, TankType::RED_FLAMINGO };

	//determines whether main loop is running or not
	bool isRunning = true;

	//contains event that is currently processed
	sf::Event event;
	///////////////////TEMP_CONTENT_BEGIN///////////////////
	glEnable(GL_DEPTH_TEST);
	modelShader = Shader("../TankSelectorModule/vertexShader.glsl", "../TankSelectorModule/fragmentShader.glsl");
	lightShader = Shader("../TankSelectorModule/lightSrcVerxShd.glsl", "../TankSelectorModule/lightSrcFragShd.glsl");
	model3d = ModelLoader::loadFromFile("../../graphics/abrams/Abrams_BF3.obj");
	//model3d = ModelLoader::loadFromFile("../../graphics/hero/nanosuit.obj");
	model3d_modelMatrix = glm::scale(model3d_modelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
	GLfloat width = gameWindow->getSize().x, height = gameWindow->getSize().y;
	projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.3f));
	viewMatrix = camera.getViewMatrix();
	arcball = ArcBall(gameWindow->getSize().x, gameWindow->getSize().y);
	Light _light;
	_light.ambientIntensity = glm::vec3(0.5f, 0.5f, 0.5f);
	_light.diffuseIntensity = glm::vec3(0.8f, 0.8f, 0.8f);
	_light.specularIntensity = glm::vec3(1.0f, 1.0f, 1.0f);
	_light.position = glm::vec3(10.0f, 3.0f, 2.0f);
	light.setLight(_light);
	light_modelMatrix = glm::scale(light_modelMatrix, glm::vec3(0.005f, 0.005f, 0.005f));
	light_modelMatrix = glm::rotate(light_modelMatrix, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	light_modelMatrix = glm::translate(light_modelMatrix, light.getLight().position);
	//hero = new Model3D("../../graphics/GM_Allison_M551_Sheridan_Cavalera_Light_Tank/GM Allison M551 'Sheridan' 'Cavalera Light Tank'.obj");
	//hero = new Model3D("../../graphics/hero/nanosuit.obj");
	//hero = new Model3D("../../graphics/Rubik's Cube/Rubik's Cube.obj");
	//hero = new Model3D("../../graphics/abrams/Abrams_BF3.obj");
	///////////////////TEMP_CONTENT_END//////////////////////

	//____Main__loop_________
	while (isRunning){

		//Check window's events
		while (gameWindow->pollEvent(event)){

			if (event.type == sf::Event::Closed)
				isRunning = false; //exit tank selector
		}


		///////////////////TEMP_CONTENT_BEGIN///////////////////
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			if (arcball.isEnabled()) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*gameWindow);
				arcball.drag(mousePosition.x, mousePosition.y);
			}
			else {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(*gameWindow);
				arcball.enable(mousePosition.x, mousePosition.y);
			}
		}
		else {
			arcball.disable();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			isRunning = false;
		}
		///////////////////TEMP_CONTENT_END//////////////////////
		
		

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
void TankSelector::draw(){

	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///////////////////TEMP_CONTENT_BEGIN///////////////////
	model3d_modelMatrix = arcball.getUpdatedModelMatrix(model3d_modelMatrix);
	modelShader.use();
	GLuint program = modelShader.getProgram();
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(model3d_modelMatrix));
	Light _light = light.getLight();
	glUniform3f(glGetUniformLocation(program, "light.ambient"), _light.ambientIntensity.x, _light.ambientIntensity.y, _light.ambientIntensity.z);
	glUniform3f(glGetUniformLocation(program, "light.diffuse"), _light.diffuseIntensity.x, _light.diffuseIntensity.y, _light.diffuseIntensity.z);
	glUniform3f(glGetUniformLocation(program, "light.specular"), _light.specularIntensity.x, _light.specularIntensity.y, _light.specularIntensity.z);
	glUniform3f(glGetUniformLocation(program, "light.position"), _light.position.x, _light.position.y, _light.position.z);
	glUniform3f(glGetUniformLocation(program, "viewPos"),camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	model3d.draw(modelShader);

	lightShader.use();
	program = lightShader.getProgram();
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(light_modelMatrix));
	light.draw(lightShader);
	///////////////////TEMP_CONTENT_END//////////////////////

	gameWindow->display();
}