#include "Game.h"

ParticleSystem firstTankExplosions(1000), secondTankExplosions(1000);

Game::Game(RenderWindow &window)
{
	isRunningGame = true;
	pointTitle.setString("Score");

	if (!font.loadFromFile("Fonts\\Lato.ttf"))
	{
		MessageBox(NULL, "No Font exist!", "ERROR", NULL);
		return;
	}
	pointTitle.setFont(font);
	pointTitle.setCharacterSize(20);
	pointTitle.setPosition(800 / 2 - pointTitle.getGlobalBounds().width / 2.f, (float)window.getSize().y - 100);

	playerOnePoints.setFont(font);
	playerOnePoints.setCharacterSize(20);
	playerOnePoints.setPosition(800 / 3 - pointTitle.getGlobalBounds().width / 2.f, (float)window.getSize().y - 100);

	playerTwoPoints.setFont(font);
	playerTwoPoints.setCharacterSize(20);
	playerTwoPoints.setPosition(800 - (800 / 3) - pointTitle.getGlobalBounds().width / 2.f, (float)window.getSize().y - 100);

	// ladowanie dzwiekow
	if ((!destroySoundBuffer.loadFromFile("Sounds\\Explosion.wav")) || (!shootSoundBuffer.loadFromFile("Sounds\\Shoot_v2.wav")) ||
		(!ricochetSoundBuffer.loadFromFile("Sounds\\Ricochet.wav")))
	{
		MessageBox(NULL, "Brak d�wi�k�w!", "ERROR", NULL);
		return;
	}
	destroySound.setBuffer(destroySoundBuffer);
	shootSound.setBuffer(shootSoundBuffer);
	shootSound.setVolume(25);
	ricochetSound.setBuffer(ricochetSoundBuffer);
}
void Game::reset()
{

	// rozpoznanie ktory gracz zostal trafiony
	if (playerOne->isHited) // trafiony gracz pierwszy
		playerTwo->setPoints(playerTwo->getPoints() + 1); // dodaj punkt graczowi drugiemu
	if (playerTwo->isHited) // trafiony gracz drugi
		playerOne->setPoints(playerOne->getPoints() + 1);// dodaj punkt graczowi pierwszemu

	// zmiana punktow z inty na stringi
	ostringstream firstPointsStream, secondPointsStream;
	firstPointsStream << playerOne->getPoints();
	playerOnePoints.setString("Player 1\n    " + firstPointsStream.str());
	secondPointsStream << playerTwo->getPoints();
	playerTwoPoints.setString("Player 2\n    " + secondPointsStream.str());


	playerOne->isHited = false;
	playerTwo->isHited = false;
	playerOne->deleteBullets();
	playerTwo->deleteBullets();
	playerOne->setTankPosition(Vector2f(760,50));
	playerTwo->setTankPosition(Vector2f(40, 50));
	playerOne->setPlayerRotation(180);
	playerTwo->setPlayerRotation(180);
}
bool Game::run(RenderWindow &window)
{
	bool backToMenu = true;
	

	playerOne = new Player("Tomek", "Textures\\1.jpg");
	playerTwo = new Player("Sinex", "Textures\\2.jpg");
	reset();
	map = new Map();
	map->createMap(window);

	// create a clock to track the elapsed time
	sf::Clock clock1, clock2;

	ParticleSystem test(1000);
	

	while (isRunningGame)
	{
		while (window.pollEvent(eventHandle))
		{
			// zmiana rozmiaru okna
			
			// klikniecie X - wyjscie z gry ca�kowite
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
			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::P))
			{
				// pocisk mozna wystrzelic tylko gdy aktualnie gracz ma mniej niz 7 wystrzelonych oraz
				// zaden z graczy nie zosta� trafiony
				if (playerOne->getBullets().size() < 8 && !playerOne->isHited && !playerTwo->isHited)
				{
					playerOne->bulletShoot();
					shootSound.play();
				}
				
			}

			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::Space))
			{
				// pocisk mozna wystrzelic tylko gdy aktualnie gracz ma mniej niz 7 wystrzelonych oraz
				// zaden z graczy nie zosta� trafiony
				if (playerTwo->getBullets().size() < 8 && !playerTwo->isHited  && !playerOne->isHited)
				{
					playerTwo->bulletShoot();
					shootSound.play();

				}

			}


		}
		// update it
		/*if (firstTankExplosions != NULL)
			if (!firstTankExplosions->update(elapsed))
			{
				delete (firstTankExplosions);
				firstTankExplosions = NULL;
			}
		if (secondTankExplosions != NULL)
			if (!secondTankExplosions->update(elapsed))
			{
				delete (secondTankExplosions);
				secondTankExplosions == NULL;
			}*/
		
		sf::Time elapsed1 = clock1.restart();
		firstTankExplosions.update(elapsed1);
		
		elapsed1 = clock2.restart();
		secondTankExplosions.update(elapsed1);
		for (vector <ParticleSystem*>::iterator it = explosions.begin(); it != explosions.end(); ++it)
		{
			(*it)->update(elapsed1);
			if ((*it)->isAlive == false){
				//delete (*it);
				//it = explosions.erase(it);
			}
		}
				

		

		window.clear();

		engine(window);
		window.draw(*map);
		if (!playerOne->isHited)
			window.draw(*playerOne);
		if (!playerTwo->isHited)
			window.draw(*playerTwo);
		window.draw(pointTitle);
		window.draw(playerOnePoints);
		window.draw(playerTwoPoints);
		/*if (firstTankExplosions != NULL)
			window.draw(*firstTankExplosions);
		if (secondTankExplosions != NULL)
			window.draw(*secondTankExplosions);*/
		for (vector <ParticleSystem*>::iterator it = explosions.begin(); it != explosions.end(); ++it)
		{
			window.draw((**it));
		}

		window.draw(firstTankExplosions);
		window.draw(secondTankExplosions);
		
		
		window.display();
	}
	return backToMenu;
}


void Game::moveTank(Player *playerMain, Player *playerSub,bool which)
{
	bool rotation = true;
	bool forwardBackward = true;
	Sprite X = playerMain->copySpriteRotation(which); // zwraca boundsy kopi sprajta podczas rotacji
	Sprite Y = playerMain->tankForwardAndBackward(which); // zwraca boundsy kopi sprajta podczas ruchu do przodu lub ty�u

	for (int i = 0; i < map->getWallsSize(); i++) // iteracja tablic ze scianami
	{
		const RectangleShape RS = map->getWallShape(i);
		if (col.isCollision(X, RS) || col.isCollision(X, playerSub->getSprite()))
			rotation = false;
		if (col.isCollision(Y, RS) || col.isCollision(Y, playerSub->getSprite()))
			forwardBackward = false;
	}
	if (rotation) // jezeli nie by�o kolizji przypisz nowa rotacje
	{
		// sprawdzanie ktory gracz i czy juz dzwiek jest wlaczony
		playerMain->assignRotation();
	}
	if (forwardBackward) // jezeli nie by�o kolizji w przod lub ty� przypisz nowa pozycje
		playerMain->moveTank();

}


void Game::detectBulletsCollision(Player *player)
{
	float right, left, top, bottom, ballX, ballY;
	for (unsigned int i = 0; i < player->getBullets().size(); i++)
	{
		for (int j = 0; j < map->getWallsSize(); j++)

		if (player->getSingleBullet(i)->getBulletBounds().intersects(map->getWall(j)->getBounds()))
		{
			float rotation = player->getBulletsShape(i).getRotation();
			float newRotation = rotation;
			right = map->getWall(j)->getBounds().left + map->getWall(j)->getBounds().width;
			left = map->getWall(j)->getBounds().left;
			top = map->getWall(j)->getBounds().top;
			bottom = map->getWall(j)->getBounds().top + map->getWall(j)->getBounds().height;
			ballX = player->getSingleBullet(i)->getPositionBullet().x;
			ballY = player->getSingleBullet(i)->getPositionBullet().y;

			if (ballX >= left && ballX <= right) // jezeli pocisk trafil w sciane pozioma
			{
				if (ballY < top)
				{
					//przypadek ze pocisk leci w dol w prawo
					if (rotation < 180 && rotation >= 90)
						newRotation = 180 - rotation;
					//przypadek ze pocisk leci w dol w lewo
					else if (rotation >= 180 && rotation <= 270)
						newRotation = rotation + 2 * (270 - rotation);

				}

				if (ballY > bottom)
				{
					//przypadek ze pocisk leci w gore w prawo
					if (rotation < 90 && rotation >= 0)
						newRotation = rotation + 2 * (90 - rotation);
					//przypadek ze pocisk leci w gore w lewo
					else if (rotation >= 270 && rotation < 360)
						newRotation = rotation - 2 * (rotation - 270);

				}


			}
			if (ballY >= top && ballY <= bottom) // jezeli pocisk trafil w pionowo
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
			ricochetSound.play();
			player->getSingleBullet(i)->setRotationBullet(newRotation);

		}

	}
};
bool Game::isPlayerHit(Player *player, Bullet *bullet)
{
	const CircleShape CS = bullet->getShape();
	if (col.isCollision(player->getSprite(), CS))
		return true;
	return false;

}
void Game::playerHited(Player *player)
{
	player->isHited = true;
}
void Game::bulletsEngine(RenderWindow &window, Player *player)
{
	
	

	detectBulletsCollision(player);

	vector <Bullet*> v = player->getBullets();
	if (!v.empty()) // jezeli wektor z pociskami nie jest pusty - czyli nastapil wystrzal i sa jakies w wektorze
	{

		for (vector <Bullet*>::iterator it = v.begin(); it != v.end(); ++it)
		{

			(*it)->updateMove(false); // updatujemy ruch pocisku

			
			if (!playerOne->isHited) // jesli jeszcze nie zostal trafiony gracz pierwszy - dzieki temu trafiony gracz
			{						// nie poch�ania pociskow po smierci
				if (isPlayerHit(playerOne, *it)) //jesli trafiony zostal gracz pierwszy
				{
					firstTankExplosions.setEmitter(playerOne->getTankPosition(), 1000);

					destroySound.play();
					playerHited(playerOne);
					delete (*it);
					it = v.erase(it);
					player->setBullets(v); // ustalamy nowy wektor setterem w klasie Player
					clock.restart();
					break;
				}
			}

			if (!playerTwo->isHited)// jesli jeszcze nie zostal trafiony gracz pierwszy - dzieki temu trafiony gracz
			{						// nie poch�ania pociskow po smierci
			if (isPlayerHit(playerTwo, *it)) //jesli trafiony zostal gracz drugi
			{
				secondTankExplosions.setEmitter(playerTwo->getTankPosition(), 1000);

				destroySound.play();
				playerHited(playerTwo);
				delete (*it);
				it = v.erase(it);
				player->setBullets(v); // ustalamy nowy wektor setterem w klasie Player
				clock.restart();
				break;
			}
			}



			if ((*it)->getElapsedTime()) // sprawdzamy czy nie ma zniknac po X sek
			{
				ParticleSystem *buff = new ParticleSystem(1000);
				buff->setEmitter((*it)->getPositionBullet(),100);
				explosions.push_back(buff);
				delete (*it);
				it = v.erase(it);

				player->setBullets(v); // ustalamy nowy wektor setterem w klasie Player
				break;
			}

			
		}
	}
	if ((playerOne->isHited || playerTwo->isHited) && (playerOne->getBullets().empty() && playerTwo->getBullets().empty()))
	{
		
		timeToRestart = clock.getElapsedTime();
		if (timeToRestart.asSeconds() > 3.f)
			reset();
		
	}
		
	for (vector <Bullet*>::iterator it = v.begin(); it != v.end(); ++it)
	{
		window.draw(**it);
	}
}


void Game::engine(RenderWindow &window)
{

	moveTank(playerOne, playerTwo,true);
	moveTank(playerTwo, playerOne,false);
	bulletsEngine(window, playerOne);
	bulletsEngine(window, playerTwo);


	
}