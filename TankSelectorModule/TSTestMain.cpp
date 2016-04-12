
/*		Entry for Tank Selector Test		*/

#include "TankSelector.h"
#include "SFML\Graphics.hpp"
#ifdef _DEBUG
#include <iostream>
#endif

int main(void){

	//create a sfml window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TankSelector");

	//launch tank selector and capture the result
	try{
		//initialize GLEW
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK) {
			throw GLEWInitError();
		}
		PlTankTypes playersTanks = TankSelector(window).run();
	}
	catch (GLEWInitError & e){
		return 1;
	}
	catch (ShaderCompileError & e){
#ifdef _DEBUG
		std::cout << e.what() << std::endl;
		system("pause");
#endif
		return 1;
	}
	catch (LoadModelError & e){
#ifdef _DEBUG
		std::cout << e.what() << std::endl;
		system("pause");
#endif
		return 1;
	}

	bool isRunning = true;
	sf::RectangleShape rectangle;
	rectangle.setPosition(sf::Vector2f(200, 200));
	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setSize(sf::Vector2f(100, 100));


	sf::Event event;
	while (isRunning) {

		
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				isRunning = false; //exit tank selector
		}

		window.clear();
		window.draw(rectangle);
		window.display();


	}



	return 0;
}