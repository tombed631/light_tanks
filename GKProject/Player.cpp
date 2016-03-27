#include "Player.h"


Player::Player(String _name, String path, float _positionX, float _positionY)
{
	if (!tankTexture.loadFromFile(path))
	{
		MessageBox(NULL, "Brak tekstury czolgu!", "ERROR", NULL);
		return;
	}
	positionX = _positionX;
	positionY = _positionY;
	tankSprite.setTexture(tankTexture);
	tankSprite.setPosition(positionX, positionY);
	tankSprite.setOrigin(80, 128);
	tankSprite.setScale(0.2, 0.2);
	tankSprite.setRotation(180);
	name = _name;

}
void Player::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(tankSprite);
};
String Player::getName()
{
	return name;
}


void Player::moveTankOne()
{
	velocity.x = 0;
	velocity.y = 0;
	sf::Time dt = deltaClock.restart();
	double angle = tankSprite.getRotation()*3.14159265 / 180;
	
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		tankSprite.setRotation((tankSprite.getRotation() - 3));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		tankSprite.setRotation((tankSprite.getRotation() + 3));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		velocity.x = (speed * sin(angle)*dt.asSeconds());
		velocity.y = -speed * cos(angle)*dt.asSeconds();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		velocity.x = -speed * sin(angle)*dt.asSeconds();
		velocity.y = speed * cos(angle)*dt.asSeconds();
	}

	tankSprite.move(velocity);

}

void Player::moveTankTwo()
{
	velocity.x = 0;
	velocity.y = 0;
	sf::Time dt = deltaClock.restart();
	double angle = tankSprite.getRotation()*3.14159265 / 180;


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		tankSprite.setRotation((tankSprite.getRotation() - 3));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		tankSprite.setRotation((tankSprite.getRotation() + 3));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		velocity.x = (speed * sin(angle)*dt.asSeconds());
		velocity.y = -speed * cos(angle)*dt.asSeconds();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		velocity.x = -speed * sin(angle)*dt.asSeconds();
		velocity.y = speed * cos(angle)*dt.asSeconds();
	}

	tankSprite.move(velocity);

}