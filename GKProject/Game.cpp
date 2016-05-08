#include "Game.h"



Game::Game(RenderWindow &window)
{
	isRunningGame = true;
	pointTitle.setString("Score");
	
	sf::Font * font = FontManager::getInstance().getFont("hongkong.ttf");
	pointTitle.setFont(*font);
	pointTitle.setCharacterSize(20);
	pointTitle.setPosition(800 / 2 - pointTitle.getGlobalBounds().width / 2.f, (float)window.getSize().y - 100);

	playerOnePoints.setFont(*font);
	playerOnePoints.setCharacterSize(20);
	playerOnePoints.setPosition(800 / 3 - pointTitle.getGlobalBounds().width / 2.f, (float)window.getSize().y - 100);

	playerTwoPoints.setFont(*font);
	playerTwoPoints.setCharacterSize(20);
	playerTwoPoints.setPosition(800 - (800 / 3) - pointTitle.getGlobalBounds().width / 2.f, (float)window.getSize().y - 100);

	// ladowanie dzwiekow
	if ((!destroySoundBuffer.loadFromFile("Sounds\\Explosion.wav")) || (!shootSoundBuffer.loadFromFile("Sounds\\Shoot_v2.wav")) ||
		(!ricochetSoundBuffer.loadFromFile("Sounds\\Ricochet.wav")))
	{
		MessageBox(NULL, "Brak dŸwiêków!", "ERROR", NULL);
		return;
	}
	if (!scoreBoardTankTextureOne.loadFromFile("Textures\\tankScoreBoardOne.png")|| !scoreBoardTankTextureTwo.loadFromFile("Textures\\tankScoreBoardTwo.png"))
	{
		MessageBox(NULL, "Brak tesktur scoreboardow!", "ERROR", NULL);
		return;
	}
	scoreBoardTankSpriteOne.setTexture(scoreBoardTankTextureOne);
	scoreBoardTankSpriteTwo.setTexture(scoreBoardTankTextureTwo);
	scoreBoardTankSpriteOne.setPosition(80, 650);
	scoreBoardTankSpriteTwo.setPosition(600, 650);
	destroySound.setBuffer(destroySoundBuffer);
	shootSound.setBuffer(shootSoundBuffer);
	shootSound.setVolume(25);
	ricochetSound.setBuffer(ricochetSoundBuffer);
	firstTankExplosions = new ParticleSystem(1000);
	secondTankExplosions = new ParticleSystem(1000);
	firstPointChanging = new ParticleSystem(100);
	secondPointChanging = new ParticleSystem(100);
}
void Game::reset()
{
	
	Vector2f pointPosition;
	// rozpoznanie ktory gracz zostal trafiony
	if (playerOne->isHited) // trafiony gracz pierwszy
	{
		playerTwo->setPoints(playerTwo->getPoints() + 1); // dodaj punkt graczowi drugiemu
		pointPosition = playerTwoPoints.getPosition();
		pointPosition.x += (playerTwoPoints.getGlobalBounds().width / 2) - 13;
		pointPosition.y += playerTwoPoints.getGlobalBounds().height - 10;
		firstPointChanging->setEmitter(pointPosition, 1000, 10, 20, false);
	}
	if (playerTwo->isHited) // trafiony gracz drugi
	{
		playerOne->setPoints(playerOne->getPoints() + 1);// dodaj punkt graczowi pierwszemu
		pointPosition = playerOnePoints.getPosition();
		pointPosition.x += (playerOnePoints.getGlobalBounds().width / 2) - 13;
		pointPosition.y += playerOnePoints.getGlobalBounds().height - 10;
		secondPointChanging->setEmitter(pointPosition, 1000, 10, 20, false);
	}

	// zmiana punktow z inty na stringi
	ostringstream firstPointsStream, secondPointsStream;
	firstPointsStream << playerOne->getPoints();
	playerOnePoints.setString(playerOne->getName() + "\n    " + firstPointsStream.str());
	secondPointsStream << playerTwo->getPoints();
	playerTwoPoints.setString(playerTwo->getName() + "\n    " + secondPointsStream.str());
	//playerOnePoints.
	playerOne->isHited = false;
	playerTwo->isHited = false;
	playerOne->deleteBullets();
	playerTwo->deleteBullets();
	playerTwo->setTankPosition(Vector2f(700,40));
	playerOne->setTankPosition(Vector2f(40, 40));
	playerOne->setPlayerRotation(180);
	playerTwo->setPlayerRotation(180);
}
bool Game::run(RenderWindow &window, p3d::PlTankColors playerColors, string playerOneName, string playerTwoName)
{
	Vector3i colorOne = Vector3i((int)255.f*playerColors.firstPlayerColor.x, (int)255.f*playerColors.firstPlayerColor.y, (int)255.f*playerColors.firstPlayerColor.z);
	Vector3i colorTwo = Vector3i((int)255.f*playerColors.secondPlayerColor.x, (int)255.f*playerColors.secondPlayerColor.y, (int)255.f*playerColors.secondPlayerColor.z);
	bool backToMenu = true;
	playerOne = new Player(playerOneName, "Textures\\tank2.png", colorOne);
	playerTwo = new Player(playerTwoName, "Textures\\tank2.png", colorTwo);
	
	
	reset();
	scoreBoardTankSpriteOne.setColor(Color(colorOne.x,colorOne.y,colorOne.z));
	scoreBoardTankSpriteTwo.setColor(Color(colorTwo.x, colorTwo.y, colorTwo.z));
	map = new Map();
	map->createMap(window);

	// create a clock to track the elapsed time
	sf::Clock clock1, clock2, clock3, clock4, clock5;


	while (isRunningGame)
	{
		while (window.pollEvent(eventHandle))
		{
			// zmiana rozmiaru okna
			
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
			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::P))
			{
				// pocisk mozna wystrzelic tylko gdy aktualnie gracz ma mniej niz 7 wystrzelonych oraz
				// zaden z graczy nie zosta³ trafiony
				if (playerOne->getBullets().size() < 8 && !playerOne->isHited && !playerTwo->isHited)
				{
					playerOne->bulletShoot();
					shootSound.play();
				}
				
			}

			if ((eventHandle.type == Event::KeyReleased && eventHandle.key.code == Keyboard::Space))
			{
				// pocisk mozna wystrzelic tylko gdy aktualnie gracz ma mniej niz 7 wystrzelonych oraz
				// zaden z graczy nie zosta³ trafiony
				if (playerTwo->getBullets().size() < 8 && !playerTwo->isHited  && !playerOne->isHited)
				{
					playerTwo->bulletShoot();
					shootSound.play();

				}

			}


		}

		sf::Time elapsed1 = clock1.restart();
		firstTankExplosions->update(elapsed1);
		elapsed1 = clock2.restart();
		secondTankExplosions->update(elapsed1);
		elapsed1 = clock3.restart();
		playerOne->getBulletExplosion()->update(elapsed1);
		playerTwo->getBulletExplosion()->update(elapsed1);

		elapsed1 = clock4.restart();
		firstPointChanging->update(elapsed1);
		elapsed1 = clock5.restart();
		secondPointChanging->update(elapsed1);

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


		// rysowanie eksplozji graczy
		window.draw(*firstTankExplosions);
		window.draw(*secondTankExplosions);
	
		// rysowanie eksplozji pocisków
		window.draw(*playerOne->getBulletExplosion());
		window.draw(*playerTwo->getBulletExplosion()); 

		// rysowanie efektów zmian punktów
		window.draw(*firstPointChanging);
		window.draw(*secondPointChanging);
		window.draw(scoreBoardTankSpriteOne);
		window.draw(scoreBoardTankSpriteTwo);
		window.display();
	}
	return backToMenu;
}


void Game::moveTank(Player *playerMain, Player *playerSub,bool which)
{
	bool rotation = true;
	bool forwardBackward = true;
	Sprite X = playerMain->copySpriteRotation(which); // zwraca boundsy kopi sprajta podczas rotacji
	Sprite Y = playerMain->tankForwardAndBackward(which); // zwraca boundsy kopi sprajta podczas ruchu do przodu lub ty³u

	for (int i = 0; i < map->getWallsSize(); i++) // iteracja tablic ze scianami
	{
		const RectangleShape RS = map->getWallShape(i);
		if (col.isCollision(X, RS) || col.isCollision(X, playerSub->getSprite()))
			rotation = false;
		if (col.isCollision(Y, RS) || col.isCollision(Y, playerSub->getSprite()))
			forwardBackward = false;
	}
	if (rotation) // jezeli nie by³o kolizji przypisz nowa rotacje
		playerMain->assignRotation();
	if (forwardBackward) // jezeli nie by³o kolizji w przod lub ty³ przypisz nowa pozycje
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
			{						// nie poch³ania pociskow po smierci
				if (isPlayerHit(playerOne, *it)) //jesli trafiony zostal gracz pierwszy
				{
					firstTankExplosions->setEmitter(playerOne->getTankPosition(), 1000, 360, 50, true);

					destroySound.play();
					playerHited(playerOne);
					delete (*it);
					it = v.erase(it);
					player->setBullets(v); // ustalamy nowy wektor setterem w klasie Player
					clock.restart();
					playerOne->setTankPosition(Vector2f(-500, -500));
					break;
				}
			}

			if (!playerTwo->isHited)// jesli jeszcze nie zostal trafiony gracz pierwszy - dzieki temu trafiony gracz
			{						// nie poch³ania pociskow po smierci
				if (isPlayerHit(playerTwo, *it)) //jesli trafiony zostal gracz drugi
				{
					secondTankExplosions->setEmitter(playerTwo->getTankPosition(), 1000, 360, 50, true);

					destroySound.play();
					playerHited(playerTwo);
					delete (*it);
					it = v.erase(it);
					player->setBullets(v); // ustalamy nowy wektor setterem w klasie Player
					clock.restart();
					playerTwo->setTankPosition(Vector2f(-500, -500));
					break;
				}
			}



			if ((*it)->getElapsedTime()) // sprawdzamy czy nie ma zniknac po X sek
			{
			
				player->setEmiter(*it);
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