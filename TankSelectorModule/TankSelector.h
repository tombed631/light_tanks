
#ifndef _TANK_SELECTOR_
#define _TANK_SELECTOR_

#include <SFML\Graphics.hpp>
#include "TankTypes.h"
#include <GL\glew.h>
#include "GLExceptions.h"
#include "Model3d.h"
#include "Camera.h"
#include "Arcball.h"

#ifdef _DEBUG
#include <iostream>
#endif

////////////////////////////////////////////////////////
///	Provides GUI for tank selecting option in game menu.
///
///	version 1.0
////////////////////////////////////////////////////////
class TankSelector final{

public:

	///////////////////TEMP_CONTENT_BEGIN//////////////////////
	Shader * shader;
	Model3D * hero;
	Camera * camera;
	ArcBall * arcball;
	glm::mat4 model_m;
	///////////////////TEMP_CONTENT_END////////////////////////

	///Default constructor.
	///Note that you need to set thetarget window 
	///before you actually use TankSelector created with default constructor.
	///See setTargetWindow method.
	TankSelector() = default;

	///Creates TankSelector.
	///sf::RenderWindow * window		Target window for rendering
	explicit TankSelector(sf::RenderWindow & window) {
		gameWindow = &window;
	}

	///Default destructor
	~TankSelector() = default;

	///Sets target window for rendering
	void setTargetWindow(sf::RenderWindow & window){
		gameWindow = &window;
	}

	///Starts TankSelector.
	///Returns tank types chose by players.
	///Throws GLEWInitError when failed to initialize GLEW
	PlTankTypes run();

private:

	///Pointer to the target window for rendering
	sf::RenderWindow * gameWindow;

	///Renders current frame to the window
	///and displays it on the screen.
	void draw();

};


#endif //_TANK_SELECTOR_