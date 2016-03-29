#include "Wall.h"


Wall::Wall(float _heigth, float _width, Vector2f _position, int _rotation)
{
	heigth = _heigth;
	width = _width;
	position = _position;
	rotation = _rotation;
	wall.setPosition(position);
	wall.setRotation(rotation);
	wall.setSize(Vector2f(width,heigth));
	wall.setFillColor(Color::White);
}


void Wall::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(wall);
};

FloatRect Wall::getBounds()
{
	return wall.getGlobalBounds();
}