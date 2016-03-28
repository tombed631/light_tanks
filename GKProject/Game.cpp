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
	


	// kod zwiazany za wyswietlenie pocisku
	vector <Bullet*> v = playerOne->getBullets();
	if (!v.empty()) // jezeli wektor z pociskami nie jest pusty - czyli nastapil wystrzal i sa jakies w wektorze
	{

		for (vector <Bullet*>::iterator it = v.begin(); it != v.end(); ++it)
		{
			(*it)->updateMove(false); // updatujemy ruch pocisku
			if ((*it)->getElapsedTime()) // sprawdzamy czy nie ma zniknac po 2 sek
			{ 
				 v.erase(it); // jezeli tak to czyscimy z tego iteratora (pocisk znika)
				 playerOne->setBullets(v); // ustalamy nowy wektor setterem w klasie Player
				 break;
			}
			window.draw((**it)); // rysujemy pocisk na scenie
		}
	}

	// dla drygiego gracza analogicznie jak wyzej
	vector <Bullet*> v2 = playerTwo->getBullets();
	if (!v2.empty())
	{

		for (vector <Bullet*>::iterator it = v2.begin(); it != v2.end(); ++it)
		{
			(*it)->updateMove(false);
			if ((*it)->getElapsedTime())
			{
				v2.erase(it);
				playerTwo->setBullets(v2);
				break;
			}
			window.draw((**it));
		}
	}



}