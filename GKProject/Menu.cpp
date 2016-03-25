#include "Menu.h"

Menu::Menu()
{
	isRunning = true;
}

void Menu::showMenu(RenderWindow &window)
{
	loadFont();
	Text title("Light Tanks", font, 40);
	title.setPosition(800 / 2 - title.getGlobalBounds().width/2.f, 20); // set position of title - 800 is 
	while (isRunning)
	{
		while (window.pollEvent(eventHandle))
		{
			if (eventHandle.type == sf::Event::Closed || (eventHandle.type == Event::KeyPressed &&
				eventHandle.key.code == Keyboard::Escape))
				isRunning = false;
			if (eventHandle.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, eventHandle.size.width, eventHandle.size.height)));
		}
		
		window.clear();
		window.draw(title);
		window.display();
	}
}
void Menu::loadFont()
{

		if (!font.loadFromFile("Fonts\\Lato.ttf"))
		{
			MessageBox(NULL, "No Font exist!", "ERROR", NULL);
			isRunning = false;
		}
}