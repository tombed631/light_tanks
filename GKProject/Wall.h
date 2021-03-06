#ifndef Wall_hpp
#define Wall_hpp


#include "Includes.h"

class Wall: public Drawable, public Transformable
{
private:
	Vector2f position; // pozycja poczatkowa
	float heigth, width; // wysokosc i szerokosc
	int rotation;
	RectangleShape wall; // ksztalt 
	Texture texture;
public:
	Wall(float _heigth, float _width, Vector2f _position, int _rotation);
	virtual void draw(RenderTarget &target, RenderStates states) const; // wirtualna metoda pozwalajaca rysowac obiekt
	FloatRect getBounds();
	const RectangleShape getShape();
	
};

#endif