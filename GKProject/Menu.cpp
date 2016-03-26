#include "Menu.h"

Menu::Menu()
{
	isRunningMenu = true;
	counter = 0;
}

void Menu::showMenu(RenderWindow &window)
{
	loadFont();
	Text title("Light Tanks", font, 40);
	title.setPosition(800 / 2 - title.getGlobalBounds().width/2.f, 20); // set position of title - 800 is 
	Text menuOptions[optionsNumber];
	string str[] = { "Play", "Choose Tank","Help", "Exit" };
	for (int i = 0; i<optionsNumber; i++)
	{
		menuOptions[i].setFont(font);
		menuOptions[i].setCharacterSize(30);
		menuOptions[i].setString(str[i]);
		menuOptions[i].setPosition(800 / 2 - menuOptions[i].getGlobalBounds().width / 2.f, 200 + i * 60);
	}
	while (isRunningMenu)
	{
		Vector2f mouse(Mouse::getPosition(window));
		while (window.pollEvent(eventHandle))
		{
			// zmiana rozmiaru okna
			if (eventHandle.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, eventHandle.size.width, eventHandle.size.height)));
			// klikniecie ESC - wyjscie
			if ((eventHandle.type == sf::Event::Closed || (eventHandle.type == Event::KeyPressed &&
				eventHandle.key.code == Keyboard::Escape)))
				isRunningMenu = false;
			// klikniecie myszka - wyjscie
			if ((menuOptions[optionsNumber - 1].getGlobalBounds().contains(mouse) &&
				eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left))
				isRunningMenu = false;
			// klikniecie enterem - wyjscie
			if (menuOptions[optionsNumber-1].getColor() == Color::Red &&
				eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Return)
				isRunningMenu = false;
			// klikniecie przyciskiem do gory - zmiejszany licznik
			if (eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Up)
			{
				if (counter <= 0)
					counter = optionsNumber - 1;
				else
					counter -= 1;
			}
			// klikniecie przyciskiem w dó³ - zwiekszany licznik
			else 
				if (eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Down)
				{
					if (counter >= optionsNumber - 1)
						counter = 0;
					else
						counter += 1;
				}
			else
				for (int i = 0; i < optionsNumber; i++)
				{
					menuOptions[i].setColor(Color::White);
					// jesli najechalismy myszka
					if (menuOptions[i].getGlobalBounds().contains(mouse)){
						counter = -1;
						if (i == 0)
							menuOptions[i].setColor(Color::Blue);
						else if (i == 1)
							menuOptions[i].setColor(Color::Green);
						else if (i == 2)
							menuOptions[i].setColor(Color::Yellow);
						else if (i == 3)
							menuOptions[i].setColor(Color::Red);
					}
					else // jesli wybralismy klawiature
					{
						if (counter == 0)
							menuOptions[counter].setColor(Color::Blue);
						else if (counter == 1)
							menuOptions[counter].setColor(Color::Green);
						else if (counter == 2)
							menuOptions[i].setColor(Color::Yellow);
						else if (counter == 3)
							menuOptions[counter].setColor(Color::Red);
					}
				}
		}
		window.clear();
		window.draw(title);
		for (int i = 0; i < optionsNumber; i++)
			window.draw(menuOptions[i]);
		window.display();
	}
}
void Menu::loadFont()
{
		if (!font.loadFromFile("Fonts\\Lato.ttf"))
		{
			MessageBox(NULL, "No Font exist!", "ERROR", NULL);
			isRunningMenu = false;
		}
}