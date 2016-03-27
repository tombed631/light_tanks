#ifndef Player_hpp
#define Player_hpp
#endif

#include "Includes.h"

class Player :public sf::Drawable, public sf::Transformable
{
private:
	Sprite tankSprite; // sprajt czo³gu
	Texture tankTexture; // textura czo³gu
	Vector2f direction;  // kierunek w ktorym porusza sie czo³g
	Vector2f velocity; //prêdkosc czo³gu
	const static int speed = 150; // szybkosc czo³gu
	Clock deltaClock; // krok czasowy
	String name; // nazwa gracza
	float positionX, positionY; // pozycja gracza
	
public:
	Player();
	void draw(RenderTarget &target, RenderStates states) const; // wirtualna metoda pozwalajaca rysowac obiekt
	Player(String _name,String path, float _positionX, float _positionY); //konstruktor z argumentamii
	String getName(); // zwraca nazwe zawodnika
	void moveTankOne(); // porusza czo³giem gracza
	void moveTankTwo(); // porusza czo³giem gracza drugiego
};