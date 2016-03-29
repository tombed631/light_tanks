#ifndef Player_hpp
#define Player_hpp
#endif

#include "Includes.h"
#include "Bullet.h"
class Player :public sf::Drawable, public sf::Transformable
{
private:
	Sprite tankSprite,copy; // sprajt czo�gu
	Texture tankTexture; // textura czo�gu
	Vector2f direction;  // kierunek w ktorym porusza sie czo�g
	Vector2f velocity; //pr�dkosc czo�gu
	const static int speed = 150; // szybkosc czo�gu
	Clock deltaClock;; // krok czasowy
	String name; // nazwa gracza
	float positionX, positionY; // pozycja gracza
	vector <Bullet*> bullets;
	
public:
	Player();
	virtual void draw(RenderTarget &target, RenderStates states) const; // wirtualna metoda pozwalajaca rysowac obiekt
	Player(String _name,String path, float _positionX, float _positionY); //konstruktor z argumentamii
	String getName(); // zwraca nazwe zawodnika
	void moveTank(); // porusza czo�giem gracza - przypisuje oryginalnego sprajta do jego kopii - jesli nie by�o kolizji
	Vector2f getTankPosition(); //zwraca pozycje czo�gu
	void bulletShoot(); // nastapil strzal - tworzenie pocisku 
	vector <Bullet*> getBullets(); // zwraca wektor z pociskami
	void setBullets(vector <Bullet*> v); // ustala wektor z pociskami
	FloatRect getBounds();
	void setTankPosition(Vector2f _position);

	FloatRect copySpriteRotation(bool tankOne); // ustawia kopie sprajta i zwraca jego boundsy podczas obrot�w
												//argument sprawdza o ktory czolg chodzi (osobne sterowanie dla pierwszego i drugiego)
	FloatRect tankForwardAndBackward(bool tankOne); // ustawia kopie sprajta w prz�d lub ty�. 
													//argument sprawdza o ktory czolg chodzi (osobne sterowanie dla pierwszego i drugiego)
	void assignRotation();	// ustawienie rotacji sprajta jako przypisanie do niego kopii kt�ra nie kolidowa�a
};