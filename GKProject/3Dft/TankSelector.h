
#ifndef _TANK_SELECTOR_
#define _TANK_SELECTOR_

#include <SFML\Graphics.hpp>
#include "TankTypes.h"
#include "GLExceptions.h"
#include "Model3d.h"
#include "ModelLoader.h"
#include "Camera.h"
#include "Arcball.h"
#include "Light.h"
#include "../FontManager.h"
#include <SFML\Graphics.hpp>
#include <sstream>
#include <iostream>

namespace p3d {

	////////////////////////////////////////////////////////
	///	Provides GUI for tank selecting option in game menu.
	/// Requires initialized GLEW to work.
	///
	///	version 1.0
	////////////////////////////////////////////////////////
	class TankSelector final {

	public:

		///Default constructor.
		///Note that you need to set the target window 
		///before you actually use TankSelector created with default constructor.
		///See setTargetWindow method.
		TankSelector();

		///Creates TankSelector.
		///sf::RenderWindow * window		Target window for rendering
		explicit TankSelector(sf::RenderWindow & window);

		///Default destructor
		~TankSelector() = default;

		///Sets target window for rendering
		void setTargetWindow(sf::RenderWindow & window);

		///Starts TankSelector.
		///Returns tank colors chose by players.
		PlTankColors run();

	private:

		///Pointer to the target window for rendering
		sf::RenderWindow * gameWindow;

		///determines whether main loop is running or not
		bool isRunning;

		///Shaders
		Shader tankShader;	
		Shader lightShader;
		///Light
		LightCube light;
		///Tank model
		Model3D tank;
		Model3D floor;
		///Transformation matrices
		glm::mat4 tankModelMatrix, lightModelMatrix, projectionMatrix;
		///Arcball
		ArcBall arcball;
		///Camera
		Camera camera;
		///Colors of players tanks.
		PlTankColors playerColors;
		///Contains color of currently seleted player.
		glm::vec3 currentPlayerColor;
		///currently selected player
		Player currentPlayer;
		
		///Color config
		int currentRGBValue;

		///Text to display
		sf::Text colorValueText[3];
		sf::Text playerText;
		sf::Text modelAuthorText;
		///Renders current frame to the window
		///and displays it on the screen.
		void draw();

		///Set up TankSelector.
		void setup();

		///Handles mouse events.
		void handleMouseEvents();

		///Handles keyboard events.
		void handleKeyboardEvents();

		///Handles window events.
		void handleWindowEvents();

		///Updates text
		void updateText();
	};

}

#endif //_TANK_SELECTOR_