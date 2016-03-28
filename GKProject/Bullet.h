#ifndef Bulet_hpp
#define Bulet_hpp
#endif

#include "Includes.h"

class Bullet : public Drawable, public Transformable
{
private:
	const int speed = 300; // szybkosc pocisku
	sf::CircleShape ball; // ksztalt 
	Vector2f position; // pozycja poczatkowa
	Vector2f velocity; //  przemieszczenie
	Time timeAlive; // czas zycia 
	Clock clock, deltaClock; // zegar generujacy czas
public:
	Bullet(Vector2f _position, float rotation);
	bool getElapsedTime(); // zwraca true jesli minelo 1 sekunda - NIE DZIALA
	virtual void draw(RenderTarget &target, RenderStates states) const; // wirtualna metoda pozwalajaca rysowac obiekt
	void updateMove(bool changeRotation); // porusza pociskiem
};