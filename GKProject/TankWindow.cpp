#include "TankWindow.h"
using namespace sf;
using namespace std;

void TankWindow::renderWindow(int height, int width, string name)
{
	RenderWindow window(sf::VideoMode(height, width, 64), name);
	window.setFramerateLimit(100);
	menu.showMenu(window);
}

