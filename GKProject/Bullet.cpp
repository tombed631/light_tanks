#include "Bullet.h"


Bullet::Bullet(Vector2f _position, float rotation)
{
	velocity.x = 0;
	velocity.y = 0;
	timeAlive = clock.restart();
	position = _position;
	bullet.setRadius((float)radius);
	bullet.setFillColor(Color::Blue);
	
	bullet.setPosition(position);
	bullet.move(Vector2f(18 * (float)sin(rotation*3.14159265 / 180), 18 * -(float)cos(rotation*3.14159265 / 180)));

	bullet.setRotation(rotation);
	bullet.setOrigin((float)radius, (float)radius);
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
	float time = dt.asSeconds();
	velocity.x = (speed * (float)sin(angle)*time);
	velocity.y = -speed * (float)cos(angle)*time;
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


