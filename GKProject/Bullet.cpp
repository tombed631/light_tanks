#include "Bullet.h"


Bullet::Bullet(Vector2f _position, float rotation)
{
	velocity.x = 0;
	velocity.y = 0;
	timeAlive = clock.restart();
	position = _position;
	ball.setRadius(5);
	ball.setFillColor(Color::White);
	ball.setPosition(position); 
	ball.setRotation(rotation);
	
}
void Bullet::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(ball);
};
bool Bullet::getElapsedTime()
{

	timeAlive = clock.getElapsedTime();
	if ((float)(timeAlive.asSeconds()) >= 1.f)
	{
		clock.restart();
		return true;
	}
	else
		return false;

}

void Bullet::updateMove(bool changeRotation)
{
	double angle = ball.getRotation()*3.14159265 / 180;
	Time dt = clock.restart();
	if (changeRotation)
	{ //kolizje
	}
	velocity.x = (speed * sin(angle)*dt.asSeconds());
	velocity.y = -speed * cos(angle)*dt.asSeconds();
	ball.move(velocity);
}