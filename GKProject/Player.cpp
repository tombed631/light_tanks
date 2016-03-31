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
	tankSprite.setScale(0.15, 0.15);
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

void Player::setTankPosition(Vector2f _position)
{
	tankSprite.setPosition(_position);

}

Sprite Player::copySpriteRotation(bool tankOne)
{
	copy = tankSprite;
	if (tankOne)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			copy.setRotation(copy.getRotation() - 3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			copy.setRotation(copy.getRotation() + 3);
	}
	else 
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			copy.setRotation(copy.getRotation() - 3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			copy.setRotation(copy.getRotation() + 3);
	}
	return copy;
}


Sprite Player::tankForwardAndBackward(bool tankOne)
{
	velocity.x = 0;
	velocity.y = 0;
	sf::Time dt = deltaClock.restart();
	double angle = tankSprite.getRotation()*3.14159265 / 180;

	if (tankOne) // jesli gracz pierwszy wykonuje ruch
	{
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
	}
	else if (!tankOne) // jesli drugi gracz
	{
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
	}
	copy.move(velocity);
	return copy;
}



void Player::assignRotation()
{
	float x = copy.getRotation();
	tankSprite.setRotation(x);
}
void Player::moveTank()
{
	tankSprite.move(velocity);
}

Vector2f Player::getTankPosition()
{
	return tankSprite.getPosition();
}

void Player::bulletShoot()
{
	Bullet *bullet = new Bullet(tankSprite.getPosition(),tankSprite.getRotation());
	bullets.push_back(bullet);
	
}

vector <Bullet*> Player::getBullets()
{
	return bullets;
}
Bullet* Player::getSingleBullet(int i)
{
	return bullets[i];
}
CircleShape Player::getBulletsShape(int i)
{
	return bullets[i]->getShape();
}


void Player::setBullets(vector <Bullet*> v)
{
	bullets = v;
}

FloatRect Player::getBounds()
{
	return tankSprite.getGlobalBounds();
}

const Sprite Player::getSprite()
{
	return tankSprite;
}
