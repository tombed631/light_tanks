#include "Bullet.h"


Bullet::Bullet(Vector2f _position, float rotation)
{
	velocity.x = 0;
	velocity.y = 0;
	timeAlive = clock.restart();
	position = _position;
	bullet.setRadius(radius);
	bullet.setFillColor(Color::Blue);
	bullet.setPosition(position);
	/*
	if (!texture.loadFromFile("Textures\\4.jpg"))
	{
		MessageBox(NULL, "Brak tekstury pocisku!", "ERROR", NULL);
		return;

	}
	*/
	//bullet.setTexture(&texture);
	bullet.setRotation(rotation);
	bullet.setOrigin(radius, radius);
	angle = 0;
}
void Bullet::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(bullet);
};
bool Bullet::getElapsedTime()
{

	timeAlive = deltaClock.getElapsedTime();
	if ((float)(timeAlive.asSeconds()) >= 4.f)//jezeli czas zycia jest wiekszy niz 5 sek to
	{
		deltaClock.restart(); // zrestartuj zegar
		return true;	// i zwroc true
	}
	else
		return false;

}

void Bullet::updateMove(bool changeRotation)
{
	angle = bullet.getRotation()*3.14159265 / 180;
	Time dt = clock.restart();
	if (changeRotation)
	{ //kolizje
	}
	velocity.x = (speed * sin(angle)*dt.asSeconds());
	velocity.y = -speed * cos(angle)*dt.asSeconds();
	bullet.move(velocity);
}

CircleShape Bullet::getShape()
{
	return bullet;
}
void Bullet::setRotationBullet(float rotation)
{
	bullet.setRotation(rotation);
}
Vector2f Bullet::getPositionBullet()
{
	return bullet.getPosition();
}

FloatRect Bullet::getBulletBounds()
{
	return bullet.getGlobalBounds();
}


