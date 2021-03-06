#include "Wall.h"


Wall::Wall(float _heigth, float _width, Vector2f _position, int _rotation)
{
	heigth = _heigth;
	width = _width;
	position = _position;
	rotation = _rotation;
	wall.setPosition(position);
	wall.setRotation((float)rotation);
	wall.setSize(Vector2f(width,heigth));
	wall.setFillColor(Color::White);
	
	if (!texture.loadFromFile("Textures\\3.jpg"))
	{
		MessageBox(NULL, "No texture of wall!", "ERROR", NULL);
		return;
	}
	wall.setTexture(&texture);
	wall.setTextureRect(IntRect(0, 0, (int)width, (int)heigth));
}


void Wall::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(wall);
};

FloatRect Wall::getBounds()
{
	return wall.getGlobalBounds();
}
const RectangleShape Wall::getShape()
{
	return wall;
}