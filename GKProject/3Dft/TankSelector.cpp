
#include "TankSelector.h"

///Determines how much color will change by one step
#define COLOR_CHANGE_STEP 0.01

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
		tankShader = Shader("../GKProject/Shaders/vertexShader.glsl", "../GKProject/Shaders/fragmentShader.glsl");
		lightShader = Shader("../GKProject/Shaders/lightSrcVerxShd.glsl", "../GKProject/Shaders/lightSrcFragShd.glsl");
		tank = ModelLoader::loadFromFile("../GKProject/Models/abrams/Abrams_BF3.obj");
		camera = Camera(glm::vec3(0.0f, 0.0f, 0.3f));
		
		playerColors = { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f) };
		currentPlayerColor = playerColors.firstPlayerColor;
		currentPlayer = Player::PLAYER_1;

		tankModelMatrix = glm::scale(tankModelMatrix, glm::vec3(0.01f, 0.01f, 0.01f));
		viewMatrix = camera.getViewMatrix();

		if (gameWindow != nullptr) {
			GLfloat width = gameWindow->getSize().x, height = gameWindow->getSize().y;
			arcball = ArcBall(width, height);
			projectionMatrix = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
		}
		
		Light _light;
		_light.ambientIntensity = glm::vec3(0.3f, 0.3f, 0.3f);
		_light.diffuseIntensity = glm::vec3(0.6f, 0.6f, 0.6f);
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
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniform3f(glGetUniformLocation(program, "light.ambient"), _light.ambientIntensity.x, _light.ambientIntensity.y, _light.ambientIntensity.z);
		glUniform3f(glGetUniformLocation(program, "light.diffuse"), _light.diffuseIntensity.x, _light.diffuseIntensity.y, _light.diffuseIntensity.z);
		glUniform3f(glGetUniformLocation(program, "light.specular"), _light.specularIntensity.x, _light.specularIntensity.y, _light.specularIntensity.z);
		glUniform3f(glGetUniformLocation(program, "light.position"), _light.position.x, _light.position.y, _light.position.z);
		glUniform3f(glGetUniformLocation(program, "viewPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
		lightShader.use();
		program = lightShader.getProgram();
		if (gameWindow != nullptr) glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(lightModelMatrix));
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
		
		//Enable depth test
		glEnable(GL_DEPTH_TEST);

		//____Main__loop_________
		while (isRunning) {

			//Check if any event occured
			handleWindowEvents();
			handleMouseEvents();
			handleKeyboardEvents();

			//display current frame
			draw();

		} //____Main__loop____end.



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

		//get tank rotation from arcball
		tankModelMatrix = arcball.getUpdatedModelMatrix(tankModelMatrix);
		
		//drawtank
		tankShader.use();
		GLuint program = tankShader.getProgram();
		glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE, glm::value_ptr(tankModelMatrix));
		glUniform3f(glGetUniformLocation(program, "color"), currentPlayerColor.r, currentPlayerColor.g, currentPlayerColor.b);
		tank.draw(tankShader);

		//draw light (optional) - uncomment next 2 following lines to draw light source.
		//lightShader.use();
		//light.draw(lightShader);
		

		gameWindow->display();
	}


	///Handles mouse events.
	void TankSelector::handleMouseEvents() {
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
	}

	///Handles keyboard events.
	void TankSelector::handleKeyboardEvents() {

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				currentPlayerColor.r += COLOR_CHANGE_STEP;
				if (currentPlayerColor.r > 1.0f)
					currentPlayerColor.r -= 1.0f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				currentPlayerColor.r -= COLOR_CHANGE_STEP;
				if (currentPlayerColor.r < 0.0f)
					currentPlayerColor.r += 1.0f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				currentPlayerColor.g += COLOR_CHANGE_STEP;
				if (currentPlayerColor.g > 1.0f)
					currentPlayerColor.g -= 1.0f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				currentPlayerColor.g -= COLOR_CHANGE_STEP;
				if (currentPlayerColor.g < 0.0f)
					currentPlayerColor.g += 1.0f;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				currentPlayerColor.b += COLOR_CHANGE_STEP;
				if (currentPlayerColor.b > 1.0f)
					currentPlayerColor.b -= 1.0f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
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
				if (event.key.code == sf::Keyboard::P) {
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
				else if (event.key.code == sf::Keyboard::Escape) {
					isRunning = false;
				}
			}
		}
	}
}


