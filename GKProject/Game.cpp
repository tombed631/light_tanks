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
				if (playerOne->getBullets().size()<8)
				playerOne->bulletShoot();
				
			}

			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::K))
			{
				if (playerTwo->getBullets().size()<8)
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
		const RectangleShape RS = map->getWallShape(i);
		if (Collision::PlayerWallCollision(X, RS))
			rotation = false;
		if (Collision::PlayerWallCollision(Y, RS))
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
	Sprite X = playerTwo->copySpriteRotation(false); // zwraca boundsy kopi sprajta podczas rotacji
	Sprite Y = playerTwo->tankForwardAndBackward(false); // zwraca boundsy kopi sprata podczas ruchu do przodu lub ty³u

	for (unsigned int i = 0; i < map->getWallsSize(); i++) // iteracja tablic ze scianami
	{
		const RectangleShape RS = map->getWallShape(i);
		if (Collision::PlayerWallCollision(X, RS))
			rotation = false;
		if (Collision::PlayerWallCollision(Y, RS))
			forwardBackward = false;
	}
	if (rotation) // jezeli nie by³o kolizji przypisz nowa rotacje
		playerTwo->assignRotation();
	if (forwardBackward) // jezeli nie by³o kolizji w przod lub ty³ przypisz nowa pozycje
		playerTwo->moveTank();


}

void Game::engine(RenderWindow &window)
{

	moveTankOne();
	moveTankTwo();
	float right, left, top, bottom, ballX, ballY;
	for (unsigned int i = 0; i < playerOne->getBullets().size(); i++)
	{
		for (unsigned int j = 0; j < map->getWallsSize(); j++)
		
		if (playerOne->getSingleBullet(i)->getBulletBounds().intersects(map->getWall(j)->getBounds()))
		{
			float rotation = playerOne->getBulletsShape(i).getRotation();
			float newRotation = rotation;
			right = map->getWall(j)->getBounds().left + map->getWall(j)->getBounds().width;
			left = map->getWall(j)->getBounds().left;
			top = map->getWall(j)->getBounds().top;
			bottom = map->getWall(j)->getBounds().top + map->getWall(j)->getBounds().height;
			ballX = playerOne->getSingleBullet(i)->getPositionBullet().x;
			ballY = playerOne->getSingleBullet(i)->getPositionBullet().y;
			
			if (ballX >= left && ballX <= right) // jezeli pocisk trafil w sciane pozioma
			{
				if (ballY > top)
				{
					//przypadek ze pocisk leci w dol w prawo
					if (rotation < 180 && rotation >= 90)
						newRotation = rotation - 2 * (rotation - 90);
					//przypadek ze pocisk leci w dol w lewo
					else if (rotation >= 180 && rotation <= 270)
						newRotation = rotation + 2 * (270 - rotation);
				}
			
				else if (ballY < bottom)
				{
					//przypadek ze pocisk leci w gore w prawo
					if (rotation < 90 && rotation >= 0)
						newRotation = rotation + 2 * (90 - rotation);
					//przypadek ze pocisk leci w gore w lewo
					else if (rotation >= 270 && rotation < 360)
						newRotation = rotation - 2 * (rotation - 270);
				}
			
				
			}
			else if (ballY >= top && ballY <= bottom) // jezeli pocisk trafil w pionowo
			{
				if (ballX <= left)
				{
					// pocisk leci w prawo w dol
					if (rotation < 180 && rotation >= 90)
						newRotation = rotation + 2 * (180 - rotation);
					// pocisk leci w prawo w gore
					if (rotation < 90 && rotation >= 0)
						newRotation = 360 - rotation;	
				}
				else if (ballX >= right)
				{
				
					// pocisk leci w lewo w dol
					if (rotation >= 180 && rotation < 270)
						newRotation = rotation - 2 * (rotation - 180);
					// pocisk leci w lewo w gore
					else if (rotation >= 270 && rotation < 360)
						newRotation = 360 - rotation;
				}
			}

			playerOne->getSingleBullet(i)->setRotationBullet(newRotation);
		}

	}




	vector <Bullet*> v = playerOne->getBullets();
	if (!v.empty()) // jezeli wektor z pociskami nie jest pusty - czyli nastapil wystrzal i sa jakies w wektorze
	{

		for (vector <Bullet*>::iterator it = v.begin(); it != v.end(); ++it)
		{
			(*it)->updateMove(false); // updatujemy ruch pocisku
			if ((*it)->getElapsedTime()) // sprawdzamy czy nie ma zniknac po 2 sek
			{

				delete (*it);
				it = v.erase(it);
				playerOne->setBullets(v); // ustalamy nowy wektor setterem w klasie Player
				break;
			}
		}





		for (vector <Bullet*>::iterator it = v.begin(); it != v.end(); ++it)
		{
			window.draw(**it);
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
				delete (*it);
				v2.erase(it);
				playerTwo->setBullets(v2);
				break;
			}
		}
		for (vector <Bullet*>::iterator it = v2.begin(); it != v2.end(); ++it)
		{
			window.draw(**it);
		}

	}

}