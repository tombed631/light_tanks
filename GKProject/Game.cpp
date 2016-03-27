#include "Game.h"

Game::Game()
{
	isRunningGame = true;
}

void Game::run(RenderWindow &window)
{
	playerOne = new Player("Tomek", "Textures\\1.jpg", 20, 20);
	playerTwo = new Player("Sinex", "Textures\\2.jpg", 50, 50);
	//players.push_back(playerOne); 
	//players.push_back(playerTwo);
	while (isRunningGame)
	{
		while (window.pollEvent(eventHandle))
		{
			// zmiana rozmiaru okna
			if (eventHandle.type == sf::Event::Resized)
				window.setView(sf::View(sf::FloatRect(0, 0, eventHandle.size.width, eventHandle.size.height)));
			// klikniecie X - wyjscie z gry ca³kowite
			if (eventHandle.type == sf::Event::Closed)
				window.close();
			// klikniecie ESC - wyjscie do menu
			if ((eventHandle.type == Event::KeyPressed && eventHandle.key.code == Keyboard::Escape))
			{
				isRunningGame = false;
				players.clear();
			}
				

		}
		playerOne->moveTankOne();
		playerTwo->moveTankTwo();
		window.clear();
		window.draw(*playerOne);
		window.draw(*playerTwo);
		window.display();
	}

}