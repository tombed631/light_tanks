#include "Game.h"

Game::Game()
{
	isRunningGame = true;
}

bool Game::run(RenderWindow &window)
{
	bool backToMenu = true;

	playerOne = new Player("Tomek", "Textures\\1.jpg", 760, 50);
	playerTwo = new Player("Sinex", "Textures\\2.jpg", 40, 50);
	map = new Map();
	map->createMap(window);

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
			if (eventHandle.type == sf::Event::Closed){
				isRunningGame = false;
				backToMenu = false;
				players.clear();
				window.close();
			}
				
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
		window.draw(*map);
		window.draw(*playerOne);
		window.draw(*playerTwo);
		window.display();
	}
	return backToMenu;
}


void Game::moveTankOne()
{
	bool rotation = true;
	bool forwardBackward = true;
	Sprite X = playerOne->copySpriteRotation(true); // zwraca boundsy kopi sprajta podczas rotacji
	Sprite Y = playerOne->tankForwardAndBackward(true); // zwraca boundsy kopi sprata podczas ruchu do przodu lub ty³u

	for (unsigned int i = 0; i < map->getWallsSize(); i++) // iteracja tablic ze scianami
	{
<<<<<<< HEAD
		if (Collision::PlayerWallCollision(X, walls[i]->getShape()))
=======
		FloatRect W = map->getWallBounds(i); // zwraca boundsy akutalnej sciany
		if (X.intersects(W))
>>>>>>> origin/szyneksmapex
			rotation = false;
		if (Collision::PlayerWallCollision(Y, walls[i]->getShape()))
			forwardBackward = false;
	}
	if (rotation) // jezeli nie by³o kolizji przypisz nowa rotacje
		playerOne->assignRotation();
	if (forwardBackward) // jezeli nie by³o kolizji w przod lub ty³ przypisz nowa pozycje
		playerOne->moveTank();

}

void Game::moveTankTwo()
{
	bool rotation = true;
	bool forwardBackward = true;
	Sprite X = playerTwo->copySpriteRotation(false);
	Sprite Y = playerTwo->tankForwardAndBackward(false);

	for (unsigned int i = 0; i < walls.size(); i++)
	{
		FloatRect W = walls[i]->getBounds();
		if (Collision::PlayerWallCollision(X, walls[i]->getShape()))
			rotation = false;
		if (Collision::PlayerWallCollision(Y, walls[i]->getShape()))
			forwardBackward = false;
	}
	if (rotation)
		playerTwo->assignRotation();
	if (forwardBackward)
		playerTwo->moveTank();

}
void Game::engine(RenderWindow &window)
{

	moveTankOne();
	moveTankTwo();
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