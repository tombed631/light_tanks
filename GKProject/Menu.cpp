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


	Text menuOptions[3];
	string str[] = { "Play", "Choose", "Exit" };

	for (int i = 0; i<3; i++)
	{
		menuOptions[i].setFont(font);
		menuOptions[i].setCharacterSize(30);
		menuOptions[i].setString(str[i]);
		menuOptions[i].setPosition(800 / 2 - menuOptions[i].getGlobalBounds().width / 2.f, 200 + i * 60);
	}

	while (isRunning)
	{
		Vector2f mouse(Mouse::getPosition(window));
		while (window.pollEvent(eventHandle))
		{
			if ((eventHandle.type == sf::Event::Closed || (eventHandle.type == Event::KeyPressed &&
				eventHandle.key.code == Keyboard::Escape)) || (menuOptions[2].getGlobalBounds().contains(mouse) &&
				eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left))
				isRunning = false;
			if (eventHandle.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, eventHandle.size.width, eventHandle.size.height)));
		}
		
		
		for (int i = 0; i<3; i++)
			if (menuOptions[i].getGlobalBounds().contains(mouse)){
				if (i == 0)
					menuOptions[i].setColor(Color::Blue);
				else if (i == 1)
					menuOptions[i].setColor(Color::Green);
				else if (i == 2)
					menuOptions[i].setColor(Color::Red);
			}
			else menuOptions[i].setColor(Color::White);


		window.clear();
		window.draw(title);
		for (int i = 0; i < 3; i++){
			window.draw(menuOptions[i]);
		}
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