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
			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::Escape))
			{
				isRunningGame = false;
				players.clear();
			}
			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::Space))
			{
				playerOne->bulletShoot();
				
			}

			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::K))
			{
				playerTwo->bulletShoot();

			}
		}

		window.clear();

		engine(window);


		window.draw(*playerOne);
		window.draw(*playerTwo);
		window.display();
	}
	
}

void Game::engine(RenderWindow &window)
{
	playerOne->moveTankOne();
	playerTwo->moveTankTwo();
	
	if (!playerOne->getBullets().empty())
	{
		vector <Bullet*> v = playerOne->getBullets();
		for (vector <Bullet*>::iterator it = v.begin(); it != v.end(); ++it)
		{
			(*it)->updateMove(false);
			if ((*it)->getElapsedTime())
			{ // nie wiem czemu tu nie wchodzi
				 delete(*it);
				 v.erase(it);
				 break;
			}
			
			
			window.draw((**it));

		}
	}

	if (!playerTwo->getBullets().empty())
	{
		vector <Bullet*> v = playerTwo->getBullets();
		for (vector <Bullet*>::iterator it = v.begin(); it != v.end(); ++it)
		{
			(*it)->updateMove(false);
			if ((*it)->getElapsedTime())
			{ // nie wiem czemu tu nie wchodzi
				delete(*it);
				v.erase(it);
				break;
			}


			window.draw((**it));

		}
	}



}