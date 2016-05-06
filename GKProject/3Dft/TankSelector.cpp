
#include "TankSelector.h"
#include <iostream>

///Determines how much color will change by one step
#define COLOR_CHANGE_STEP 0.01
///Button used to activate arcball (== start rotating tank model)
#define ARCBALL_ACTIVATE_BUTTON	sf::Mouse::Middle
///Button used to switch between players
#define SWITCH_PLAYER_BUTTON sf::Keyboard::P
///Buttons used to configure color
#define INCREASE_RGBVALUE_BUTTON sf::Keyboard::Up
#define DECREASE_RGBVALUE_BUTTON sf::Keyboard::Down
#define CONFIG_RGBVALUE_R_BUTTON sf::Keyboard::R
#define CONFIG_RGBVALUE_G_BUTTON sf::Keyboard::G
#define CONFIG_RGBVALUE_B_BUTTON sf::Keyboard::B
///Button used to return to the game menu
#define RETURN_TO_MENU_BUTTON sf::Keyboard::Escape
///Defines camera settings
#define CAMERA_DEFAULT_DISTANCE 1.0f
#define CAMERA_MIN_DISTANCE 0.5f
#define CAMERA_MAX_DISTANCE 2.0f
#define CAMERA_DISTANCE_STEP 0.05f
///Defines text parameters
#define TEXT_CHARACTER_SIZE 15

namespace p3d {

	///Default constructor.
	///Note that you need to set thetarget window 
	///before you actually use TankSelector created with default constructor.
	///See setTargetWindow method.
	TankSelector::TankSelector()
	{
		gameWindow = nullptr;
		setup();
	}

	///Creates TankSelector.
	///sf::RenderWindow * window		Target window for rendering
	TankSelector::TankSelector(sf::RenderWindow & window) {
		gameWindow = &window;
		setup();
	}

	///Sets up TankSelector
	void TankSelector::setup() {
		isRunning = false;
		tankShader = Shader("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
		lightShader = Shader("Shaders/lightSrcVerxShd.glsl", "Shaders/lightSrcFragShd.glsl");
		tank = ModelLoader::loadFromFile("Models/Tank/Tank.obj");
		floor = ModelLoader::loadFromFile("Models/floor/floor.obj");
		camera = Camera(glm::vec3(0.0f, 0.2f, 1.0f));

		playerColors = { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) };

		tankModelMatrix = glm::scale(tankModelMatrix, glm::vec3(0.05f, 0.05f, 0.05f));

		if (gameWindow != nullptr) {
			GLfloat width = gameWindow->getSize().x, height = gameWindow->getSize().y;
			arcball = ArcBall(width, height);
			projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
		}
		
		Light _light;
		_light.ambientIntensity = glm::vec3(0.3f, 0.3f, 0.3f);
		_light.diffuseIntensity = glm::vec3(0.7f, 0.7f, 0.7f);
		_light.specularIntensity = glm::vec3(1.0f, 1.0f, 1.0f);
		_light.position = glm::vec3(0.0f, 3.0f, 10.0f);
		light.setLight(_light);
		lightModelMatrix = glm::scale(lightModelMatrix, glm::vec3(0.005f, 0.005f, 0.005f));
		lightModelMatrix = glm::translate(lightModelMatrix, light.getLight().position);
		lightModelMatrix = glm::rotate(lightModelMatrix, glm::radians(30.0f), glm::vec3(1.0f, 1.0f, 1.0f));


		//set up some shader variables that won't change
		tankShader.use();
		GLuint program = tankShader.getProgram();
		if (gameWindow != nullptr) glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniform3f(glGetUniformLocation(program, "light.ambient"), _light.ambientIntensity.x, _light.ambientIntensity.y, _light.ambientIntensity.z);
		glUniform3f(glGetUniformLocation(program, "light.diffuse"), _light.diffuseIntensity.x, _light.diffuseIntensity.y, _light.diffuseIntensity.z);
		glUniform3f(glGetUniformLocation(program, "light.specular"), _light.specularIntensity.x, _light.specularIntensity.y, _light.specularIntensity.z);
		glUniform3f(glGetUniformLocation(program, "light.position"), _light.position.x, _light.position.y, _light.position.z);
		glUniform3f(glGetUniformLocation(program, "viewPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		lightShader.use();
		program = lightShader.getProgram();
		if (gameWindow != nullptr) glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(lightModelMatrix));

		//text settings
		sf::Font * font = FontManager::getInstance().getFont("Lato.ttf");
		playerText.setFont(*font);
		playerText.setPosition(10, 10);
		playerText.setCharacterSize(TEXT_CHARACTER_SIZE);
		for (unsigned int i = 0; i < 3; i++) {
			colorValueText[i].setFont(*font);
			colorValueText[i].setPosition(10, (i+1) * 20 + 10);
			colorValueText[i].setCharacterSize(TEXT_CHARACTER_SIZE);
		}
	}

	///Sets target window for rendering
	void TankSelector::setTargetWindow(sf::RenderWindow & window) {
		gameWindow = &window;
		GLfloat width = gameWindow->getSize().x, height = gameWindow->getSize().y;
		arcball.setWindowSize(width, height);
		projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
		GLuint program = tankShader.getProgram();
		tankShader.use();
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		lightShader.use();
		glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	}

	///Starts TankSelector.
	///Returns tank colors chose by players.
	PlTankColors TankSelector::run() {

		isRunning = true;
		//Select currently configured player as player 1
		currentPlayerColor = playerColors.firstPlayerColor;
		currentPlayer = Player::PLAYER_1;
		//Set default camera distance
		glm::vec3 cameraPos = camera.getPosition();
		cameraPos.z = CAMERA_DEFAULT_DISTANCE;
		camera.setPosition(cameraPos);

		
		//Enable depth test
		glEnable(GL_DEPTH_TEST);

		//____Main__loop_________
		while (isRunning) {

			//Check if any event occured
			handleWindowEvents();
			handleMouseEvents();
			handleKeyboardEvents();

			updateText();
		
			//display current frame
			draw();

		} //____Main__loop____end.

		//Store last configured color
		if (currentPlayer == Player::PLAYER_1)
			playerColors.firstPlayerColor = currentPlayerColor;
		else 
			playerColors.secondPlayerColor = currentPlayerColor;
		


		// prepare context for SFML
		glUseProgram(0);	//set default openGL shader program
		glDisable(GL_DEPTH_TEST);	//Disable depth test
		gameWindow->resetGLStates();	//restore SFML's openGL states

		return playerColors;
	}


	///Renders current frame to the window
	///and displays it on the screen.
	void TankSelector::draw() {

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 viewMatrix = camera.getViewMatrix();
		tankShader.use();
		GLuint program = tankShader.getProgram();

		//draw floor
		glm::mat4 floorModelMatrix;
		floorModelMatrix = glm::scale(floorModelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
		floorModelMatrix = glm::translate(floorModelMatrix, glm::vec3(0.0f, 0.03f, 0.0f));
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(floorModelMatrix));
		glUniform3f(glGetUniformLocation(program, "color"), 1.0f, 1.0f, 1.0f);
		floor.draw(tankShader);

		//get tank rotation from arcball
		tankModelMatrix = arcball.getUpdatedModelMatrix(tankModelMatrix);
		
		//draw tank
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(tankModelMatrix));
		glUniform3f(glGetUniformLocation(program, "color"), currentPlayerColor.r, currentPlayerColor.g, currentPlayerColor.b);
		tank.draw(tankShader);

		//draw light (optional) - uncomment next 2 following lines to draw light source.
		//lightShader.use();
		//light.draw(lightShader);
		
		//Draw text
		gameWindow->pushGLStates();
		gameWindow->draw(playerText);
		for (unsigned int i = 0; i < 3; i++)
			gameWindow->draw(colorValueText[i]);
		gameWindow->popGLStates();

		gameWindow->display();
	}


	///Handles mouse events.
	void TankSelector::handleMouseEvents() {
		if (sf::Mouse::isButtonPressed(ARCBALL_ACTIVATE_BUTTON)) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*gameWindow);
			int winWidth = gameWindow->getSize().x;
			int winHeight = gameWindow->getSize().y;
			if (mousePosition.x > winWidth)
				mousePosition.x = winWidth;
			else if (mousePosition.x < 0)
				mousePosition.x = 0;
			mousePosition.y = winHeight / 2;

			if (arcball.isEnabled())
				arcball.drag(mousePosition.x, mousePosition.y);
			else
				arcball.enable(mousePosition.x, mousePosition.y);
		}
		else {
			arcball.disable();
		}
	}

	///Handles keyboard events.
	void TankSelector::handleKeyboardEvents() {

		if (sf::Keyboard::isKeyPressed(CONFIG_RGBVALUE_R_BUTTON)) {
			if (sf::Keyboard::isKeyPressed(INCREASE_RGBVALUE_BUTTON)) {
				currentPlayerColor.r += COLOR_CHANGE_STEP;
				if (currentPlayerColor.r > 1.0f)
					currentPlayerColor.r -= 1.0f;
			}
			else if (sf::Keyboard::isKeyPressed(DECREASE_RGBVALUE_BUTTON)) {
				currentPlayerColor.r -= COLOR_CHANGE_STEP;
				if (currentPlayerColor.r < 0.0f)
					currentPlayerColor.r += 1.0f;
			}
		}
		if (sf::Keyboard::isKeyPressed(CONFIG_RGBVALUE_G_BUTTON)) {
			if (sf::Keyboard::isKeyPressed(INCREASE_RGBVALUE_BUTTON)) {
				currentPlayerColor.g += COLOR_CHANGE_STEP;
				if (currentPlayerColor.g > 1.0f)
					currentPlayerColor.g -= 1.0f;
			}
			else if (sf::Keyboard::isKeyPressed(DECREASE_RGBVALUE_BUTTON)) {
				currentPlayerColor.g -= COLOR_CHANGE_STEP;
				if (currentPlayerColor.g < 0.0f)
					currentPlayerColor.g += 1.0f;
			}
		}
		if (sf::Keyboard::isKeyPressed(CONFIG_RGBVALUE_B_BUTTON)) {
			if (sf::Keyboard::isKeyPressed(INCREASE_RGBVALUE_BUTTON)) {
				currentPlayerColor.b += COLOR_CHANGE_STEP;
				if (currentPlayerColor.b > 1.0f)
					currentPlayerColor.b -= 1.0f;
			}
			else if (sf::Keyboard::isKeyPressed(DECREASE_RGBVALUE_BUTTON)) {
				currentPlayerColor.b -= COLOR_CHANGE_STEP;
				if (currentPlayerColor.b < 0.0f)
					currentPlayerColor.b += 1.0f;
			}
		}
	}

	///Handles window events.
	void TankSelector::handleWindowEvents() {

		//contains event that is currently processed
		sf::Event event;

		while (gameWindow->pollEvent(event)) {

			if (event.type == sf::Event::Closed)
				isRunning = false; //exit tank selector
			else if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == SWITCH_PLAYER_BUTTON) {
					if (currentPlayer == Player::PLAYER_1) {
						//save player 1 color
						playerColors.firstPlayerColor = currentPlayerColor;
						//change to player 2
						currentPlayerColor = playerColors.secondPlayerColor;
						currentPlayer = Player::PLAYER_2;
					}
					else {
						playerColors.secondPlayerColor = currentPlayerColor;
						currentPlayerColor = playerColors.firstPlayerColor;
						currentPlayer = Player::PLAYER_1;
					}
				}
				else if (event.key.code == RETURN_TO_MENU_BUTTON) {
					isRunning = false;
				}
			}
			else if (event.type == sf::Event::MouseWheelMoved) {
				glm::vec3 cameraPos = camera.getPosition();
				cameraPos.z -= event.mouseWheel.delta * CAMERA_DISTANCE_STEP;
				if (cameraPos.z > CAMERA_MAX_DISTANCE)
					cameraPos.z = CAMERA_MAX_DISTANCE;
				else if (cameraPos.z < CAMERA_MIN_DISTANCE)
					cameraPos.z = CAMERA_MIN_DISTANCE;
				camera.setPosition(cameraPos);
			}
		}
	}

	///Updates text
	void TankSelector::updateText()
	{
		std::stringstream stream;
		stream.precision(2);
		stream.setf(std::ios::fixed);
		stream << currentPlayerColor.r;
		colorValueText[0].setString("R = " + stream.str());
		stream.clear();
		stream.str(std::string());	//clear sstream
		stream << currentPlayerColor.g;
		colorValueText[1].setString("G = " + stream.str());
		stream.clear();
		stream.str(std::string());	//clear sstream
		stream << currentPlayerColor.b;
		colorValueText[2].setString("B = " + stream.str());
		if (currentPlayer == Player::PLAYER_1)
			playerText.setString("Player: 1");
		else
			playerText.setString("Player: 2");
	}
}


