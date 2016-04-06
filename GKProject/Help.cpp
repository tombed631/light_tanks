#include "Help.h"

Help::Help()
{
	isRunningHelp = true;
}

bool Help::showHelp(RenderWindow &window)
{
	bool backToMenu = true;

	loadFont();
	Text title("Help", font, 40);
	title.setPosition(800 / 2 - title.getGlobalBounds().width / 2.f, 20); // set position of title - 800 is 
	Text firstHelpTitle, firstHelpMove, firstHelpShoot, secondHelpTitle, secondHelpMove, secondHelpShoot, backText;
	Sprite arrowKeysSprite, wsadKeysSprite, spaceKeySprite, pKeySprite;
	Texture arrowKeysImage, wsadKeysImage, spaceKeyImage, pKeyImage;

	if ((!arrowKeysImage.loadFromFile("Textures\\arrowKeys.png")) || (!wsadKeysImage.loadFromFile("Textures\\WSAD.png")) ||
		(!spaceKeyImage.loadFromFile("Textures\\spacebar.png")) || (!pKeyImage.loadFromFile("Textures\\pKey.png")))
	{
		MessageBox(NULL, "Brak tekstury klawisza!", "ERROR", NULL);
		return false;
	}

	// text powrotu
	backText.setString("Back to menu");
	backText.setFont(font);
	backText.setCharacterSize(30);
	
	

	// tworzenie opisu sterowania 1 gracza
	firstHelpTitle.setString("Player 1");
	firstHelpTitle.setFont(font);
	firstHelpTitle.setCharacterSize(30);
	firstHelpTitle.setPosition(200 - firstHelpTitle.getGlobalBounds().width / 2.f, (float)200);
	textsVector.push_back(firstHelpTitle);

	firstHelpMove.setString("Move:");
	firstHelpMove.setFont(font);
	firstHelpMove.setCharacterSize(30);
	firstHelpMove.setPosition(middlePosition(firstHelpTitle) - firstHelpMove.getGlobalBounds().width/2.f, firstHelpTitle.getPosition().y + firstHelpTitle.getGlobalBounds().height + 10);
	textsVector.push_back(firstHelpMove);

	arrowKeysSprite.setTexture(arrowKeysImage);
	arrowKeysSprite.setPosition(middlePosition(firstHelpMove) - arrowKeysSprite.getGlobalBounds().width / 2.f, firstHelpMove.getPosition().y + firstHelpMove.getGlobalBounds().height + 10);
	imagesVector.push_back(arrowKeysSprite);

	firstHelpShoot.setString("Shoot:");
	firstHelpShoot.setFont(font);
	firstHelpShoot.setCharacterSize(30);
	firstHelpShoot.setPosition(middlePosition(firstHelpTitle) - firstHelpShoot.getGlobalBounds().width / 2.f, arrowKeysSprite.getPosition().y + arrowKeysSprite.getGlobalBounds().height + 10);
	textsVector.push_back(firstHelpShoot);

	pKeySprite.setTexture(pKeyImage);
	pKeySprite.setPosition(middlePosition(firstHelpShoot) - pKeySprite.getGlobalBounds().width / 2.f, firstHelpShoot.getPosition().y + firstHelpShoot.getGlobalBounds().height + 10);
	imagesVector.push_back(pKeySprite);
	

	// opis sterowania 2 gracza
	secondHelpTitle.setString("Player 2");
	secondHelpTitle.setFont(font);
	secondHelpTitle.setCharacterSize(30);
	secondHelpTitle.setPosition(600 - secondHelpTitle.getGlobalBounds().width / 2.f, (float)200);
	textsVector.push_back(secondHelpTitle);

	secondHelpMove.setString("Move:");
	secondHelpMove.setFont(font);
	secondHelpMove.setCharacterSize(30);
	secondHelpMove.setPosition(middlePosition(secondHelpTitle) - secondHelpMove.getGlobalBounds().width / 2.f, secondHelpTitle.getPosition().y + secondHelpTitle.getGlobalBounds().height + 10);
	textsVector.push_back(secondHelpMove);

	wsadKeysSprite.setTexture(wsadKeysImage);
	wsadKeysSprite.setPosition(middlePosition(secondHelpMove) - wsadKeysSprite.getGlobalBounds().width / 2.f, secondHelpMove.getPosition().y + secondHelpMove.getGlobalBounds().height + 10);
	imagesVector.push_back(wsadKeysSprite);

	secondHelpShoot.setString("Shoot:");
	secondHelpShoot.setFont(font);
	secondHelpShoot.setCharacterSize(30);
	secondHelpShoot.setPosition(middlePosition(secondHelpTitle) - secondHelpShoot.getGlobalBounds().width / 2.f, wsadKeysSprite.getPosition().y + wsadKeysSprite.getGlobalBounds().height + 10);
	textsVector.push_back(secondHelpShoot);

	spaceKeySprite.setTexture(spaceKeyImage);
	spaceKeySprite.setPosition(middlePosition(secondHelpShoot) - spaceKeySprite.getGlobalBounds().width / 2.f, secondHelpShoot.getPosition().y + secondHelpShoot.getGlobalBounds().height + 10);
	imagesVector.push_back(spaceKeySprite);
	
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
			if (backText.getColor() == Color::Red &&
				(eventHandle.type == Event::MouseButtonReleased && eventHandle.key.code == Mouse::Left))
				isRunningHelp = false;
		
			backText.setColor(Color::White);
			// jesli najechalismy myszka
			if (backText.getGlobalBounds().contains(mouse)){
				backText.setColor(Color::Red);
			}
				
		}
		window.clear();
		window.draw(title);
		window.draw(backText);
		for (unsigned int i = 0; i < textsVector.size(); i++)
			window.draw(textsVector[i]);
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

float Help::middlePosition(Text object)
{
	return object.getPosition().x + object.getGlobalBounds().width / 2.f;
}