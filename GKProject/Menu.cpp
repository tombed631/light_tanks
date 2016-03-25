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


	Text tekst[3];


	string str[] = { "Play", "Choose", "Exit" };
	for (int i = 0; i<3; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(30);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(800 / 2 - tekst[i].getGlobalBounds().width / 2.f, 200 + i * 60);
	}

	// pierwsza opcja- graj
	Text firstOption("Graj", font, 30);
	firstOption.setPosition(800 / 2 - firstOption.getGlobalBounds().width / 2.f, 200);

	// druga opcja - wybor czolgu
	Text secondOption("Wybierz czolg", font, 30);
	secondOption.setPosition(800 / 2 - secondOption.getGlobalBounds().width / 2.f, 300);

	// trzecia opcja - wyjscie
	Text thirdOption("Wybierz czolg", font, 30);
	secondOption.setPosition(800 / 2 - secondOption.getGlobalBounds().width / 2.f, 300);

	while (isRunning)
	{
		Vector2f mouse(Mouse::getPosition(window));
		while (window.pollEvent(eventHandle))
		{
			if ((eventHandle.type == sf::Event::Closed || (eventHandle.type == Event::KeyPressed &&
				eventHandle.key.code == Keyboard::Escape)) || (tekst[2].getGlobalBounds().contains(mouse) &&
				eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left))
				isRunning = false;
			if (eventHandle.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, eventHandle.size.width, eventHandle.size.height)));
		}
		
		for (int i = 0; i<3; i++)
			if (tekst[i].getGlobalBounds().contains(mouse)){
				if (i == 0)
					tekst[i].setColor(Color::Blue);
				else if (i == 1)
					tekst[i].setColor(Color::Green);
				else if (i == 2)
					tekst[i].setColor(Color::Red);
			}
			else tekst[i].setColor(Color::White);


		window.clear();
		window.draw(title);
		for (int i = 0; i < 3; i++){
			window.draw(tekst[i]);
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