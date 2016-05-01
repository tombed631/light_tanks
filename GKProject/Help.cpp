#include "Help.h"

Help::Help()
{
	isRunningHelp = true;
}

bool Help::showHelp(RenderWindow &window, p3d::PlTankColors colors)
{
	bool backToMenu = true;

	loadFont();
	Text title("Help", font, 40);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2.f, 20); // set position of title - 800 is 
	Text texts[6];
	
	String strings[] = { "Back", "Player 1", "Player 2", "Move", "Shoot" };
	
	
	if ((!arrowKeysTexture.loadFromFile("Textures\\arrows.png")) || (!wsadKeysTexture.loadFromFile("Textures\\wsad.png")) ||
		(!spaceKeyTexture.loadFromFile("Textures\\Space.png")) || (!pKeyTexture.loadFromFile("Textures\\pKey.png")))
	{
		MessageBox(NULL, "Brak tekstury klawisza!", "ERROR", NULL);
		return false;
	}



	
	for (int i = 0; i < 5; i++)
	{
		texts[i].setString(strings[i]);
		texts[i].setFont(font);
		texts[i].setCharacterSize(30);
			texts[1].setPosition(550/ 2 - texts[1].getGlobalBounds().width / 2.f, 100.f + 100.f); //player1
			texts[2].setPosition(1100 / 2 - texts[2].getGlobalBounds().width / 2.f, 100.f +  100.f); // player2

			if (i>2)
				texts[i].setPosition(200 / 2 - texts[i].getGlobalBounds().width / 2.f, 50.f + (i) * 100.f);// move i shoot
	}
	

	arrowKeysSprite.setTexture(arrowKeysTexture);
	
	
	arrowKeysSprite.setPosition(550 / 2 - arrowKeysSprite.getGlobalBounds().width / 2.f, 100.f + 200.f); //player1
	pKeySprite.setPosition(500 / 2 - pKeySprite.getGlobalBounds().width / 2.f, 100.f + 350); //player1
	wsadKeysSprite.setTexture(wsadKeysTexture);
	
	wsadKeysSprite.setPosition(1100 / 2 - wsadKeysSprite.getGlobalBounds().width / 2.f, 100.f + 200.f); //player1
	spaceKeySprite.setTexture(spaceKeyTexture);
	spaceKeySprite.setPosition(1100 / 2 - spaceKeySprite.getGlobalBounds().width / 2.f, 100.f + 350.f); //player1
	pKeySprite.setTexture(pKeyTexture);
	Vector3i colorOne = Vector3i((int)255.f*colors.firstPlayerColor.x, (int)255.f*colors.firstPlayerColor.y, (int)255.f*colors.firstPlayerColor.z);
	Vector3i colorTwo = Vector3i((int)255.f*colors.secondPlayerColor.x, (int)255.f*colors.secondPlayerColor.y, (int)255.f*colors.secondPlayerColor.z);
	if ((colors.firstPlayerColor.x == 0 && colors.firstPlayerColor.y == 0 && colors.firstPlayerColor.z == 0))
	{
		arrowKeysSprite.setColor(Color::White);
		pKeySprite.setColor(Color::White);
		
	}
	else
	{
		arrowKeysSprite.setColor(Color(colorOne.x, colorOne.y, colorOne.z));
		pKeySprite.setColor(Color(colorOne.x, colorOne.y, colorOne.z));
	}
	if (colors.secondPlayerColor.x == 0 && colors.secondPlayerColor.y == 0 && colors.secondPlayerColor.z == 0)
	{
		wsadKeysSprite.setColor(Color::White);
		spaceKeySprite.setColor(Color::White);
	}
	else
	{
		wsadKeysSprite.setColor(Color(colorTwo.x, colorTwo.y, colorTwo.z));
		spaceKeySprite.setColor(Color(colorTwo.x, colorTwo.y, colorTwo.z));	
	}
		
	imagesVector.push_back(arrowKeysSprite);
	imagesVector.push_back(wsadKeysSprite);
	imagesVector.push_back(spaceKeySprite);
	imagesVector.push_back(pKeySprite);


	while (isRunningHelp)
	{
		Vector2f mouse(Mouse::getPosition(window));
		while (window.pollEvent(eventHandle))
		{
			// klikniecie ESC - wyjscie
			if ((eventHandle.type == sf::Event::Closed || (eventHandle.type == Event::KeyPressed &&
				eventHandle.key.code == Keyboard::Escape)))
				isRunningHelp = false;

			// klikniecie X - wyjscie z gry ca³kowite
			if (eventHandle.type == sf::Event::Closed){
				isRunningHelp = false;
				backToMenu = false;
				window.close();
			}
			// klikniecie myszka lub klawiatura na wyjscie
			if (texts[0].getColor() == Color::Red &&
				(eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left))
				isRunningHelp = false;
		
			texts[0].setColor(Color::White);
			// jesli najechalismy myszka
			if (texts[0].getGlobalBounds().contains(mouse)){
				texts[0].setColor(Color::Red);
			}
				
		}
		window.clear();
		window.draw(title);
		
		for (unsigned int i = 0; i < 6; i++)
			window.draw(texts[i]);
		for (unsigned int i = 0; i < imagesVector.size(); i++)
			window.draw(imagesVector[i]);
		window.display();
	}
	return backToMenu;
}

void Help::loadFont()
{
	if (!font.loadFromFile("Fonts\\Lato.ttf"))
	{
		MessageBox(NULL, "No Font exist!", "ERROR", NULL);
		isRunningHelp = false;
	}
}