#include "Menu.h"

Menu::Menu()
{
	isRunningMenu = true;
	counter = 0;
}
void Menu::showWarning(Time &time)
{
	
	
	chooseColorText.setString("First Choose color!");
	chooseColorText.setFont(font);
	chooseColorText.setCharacterSize(20);
	chooseColorText.setColor(Color::Red);
	chooseColorText.setPosition(800 / 2 - chooseColorText.getGlobalBounds().width / 2.f, (float)700);

	
	if (time.asSeconds() > 1.5)
	{

		isWarningShow = false;
		
	}
}
void Menu::showMenu(RenderWindow &window)
{
	
	Clock clock;
	p3d::PlTankColors playerColors; // kolory graczy
	loadFont();
	bool isColorChoose = false;
	Text authors("Inf sem.6 GKiO1\nAuthors:\nTomasz Bednarek\nBartlomiej Rys\nMarcin Adrian", font, 15);
	authors.setPosition(700 - authors.getGlobalBounds().width / 2.f, (float)window.getSize().y - 100);
	Text title("Light Tanks", font, 40);
	title.setPosition(800 / 2 - title.getGlobalBounds().width/2.f, 20); // set position of title - 800 is 
	Text menuOptions[optionsNumber];
	string str[] = { "Play", "Choose color","Controls", "Exit" };
	for (int i = 0; i<optionsNumber; i++)
	{
		menuOptions[i].setFont(font);
		menuOptions[i].setCharacterSize(30);
		menuOptions[i].setString(str[i]);
		menuOptions[i].setPosition(800 / 2 - menuOptions[i].getGlobalBounds().width / 2.f, (float)200 + i * 60);
	}
	while (isRunningMenu)
	{
		Vector2f mouse(Mouse::getPosition(window));
		while (window.pollEvent(eventHandle))
		{
			// klikniecie ESC - wyjscie
			if ((eventHandle.type == sf::Event::Closed || (eventHandle.type == Event::KeyPressed &&
				eventHandle.key.code == Keyboard::Escape)))
				isRunningMenu = false;
			// klikniecie myszka lub klawiatura na wyjscie
			if (menuOptions[optionsNumber - 1].getColor() == Color::Red && 
				((eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left)
				|| (eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Return)))
				isRunningMenu = false;

			// klikniecie myszka na wybor czolgu
			if (menuOptions[optionsNumber - 3].getColor() == Color::Green &&
				((eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left)
				|| (eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Return)))
			{
				
				tankSelector.setTargetWindow(window);	//set window
				playerColors = tankSelector.run();	//run tank selector
					
				isWarningShow = false;
			
				isColorChoose = true;

			}

			// klikniecie myszka lub klawiatura na PLAY
			if (menuOptions[optionsNumber - 4].getColor() == Color::Blue &&
				((eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left)
				 || (eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Return)))
			{
				Time time = clock.restart();
				
				
				if (!isColorChoose)
				{

						isWarningShow = true;
						time = clock.getElapsedTime();
						showWarning(time);
						
				}
				else
				{
					Game game(window);
					// trzeba tez zaimplementowac sprawdzenie wybranie czolgu - potem
					isRunningMenu = game.run(window, playerColors);
				}
				
			}
				
			// klikniecie myszka lub klawiatura na HELP
			if (menuOptions[optionsNumber - 2].getColor() == Color::Yellow &&
				((eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left)
				|| (eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Return)))
			{
				Help help;
				// trzeba tez zaimplementowac sprawdzenie wybranie czolgu - potem
				isRunningMenu = help.showHelp(window);
			}


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
							menuOptions[counter].setColor(Color::Yellow);
						else if (counter == 3)
							menuOptions[counter].setColor(Color::Red);
					}
				}
		}
		window.clear();
		window.draw(title);
		for (int i = 0; i < optionsNumber; i++)
			window.draw(menuOptions[i]);
		if (isWarningShow)
			window.draw(chooseColorText);
		window.draw(authors);
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