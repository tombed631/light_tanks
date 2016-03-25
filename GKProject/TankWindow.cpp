#include "TankWindow.h"
using namespace sf;
using namespace std;

void TankWindow::renderWindow(int height, int width, string name)
{
	RenderWindow window(sf::VideoMode(height, width, 32), name);
	menu.showMenu(window);
}

