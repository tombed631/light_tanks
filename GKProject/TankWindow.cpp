#include "TankWindow.h"
#include "3Dft\GLExceptions.h"
using namespace sf;
using namespace std;

void TankWindow::renderWindow(int height, int width, string name)
{
	RenderWindow window(sf::VideoMode(height, width, 64), name,sf::Style::Default, sf::ContextSettings(24));
	window.setFramerateLimit(100);

	//initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		throw p3d::GLEWInitError();	//throw ex and shut down the game or remove 3d from game XD
	}

	//menu.showMenu(window);
	Menu().showMenu(window);
}

