#ifndef Player_hpp
#define Player_hpp
#endif

#include "Includes.h"
#include "Bullet.h"
class Player :public sf::Drawable, public sf::Transformable
{
private:
	Sprite tankSprite,copy; // sprajt czo³gu
	Texture tankTexture; // textura czo³gu
	Vector2f direction;  // kierunek w ktorym porusza sie czo³g
	Vector2f velocity; //prêdkosc czo³gu
	const static int speed = 150; // szybkosc czo³gu
	Clock deltaClock;; // krok czasowy
	String name; // nazwa gracza
	float positionX, positionY; // pozycja gracza
	vector <Bullet*> bullets;
	
public:
	Player();
	virtual void draw(RenderTarget &target, RenderStates states) const; // wirtualna metoda pozwalajaca rysowac obiekt
	Player(String _name,String path, float _positionX, float _positionY); //konstruktor z argumentamii
	String getName(); // zwraca nazwe zawodnika
	void moveTank(); // porusza czo³giem gracza - przypisuje oryginalnego sprajta do jego kopii - jesli nie by³o kolizji
	Vector2f getTankPosition(); //zwraca pozycje czo³gu
	void bulletShoot(); // nastapil strzal - tworzenie pocisku 
	vector <Bullet*> getBullets(); // zwraca wektor z pociskami
	void setBullets(vector <Bullet*> v); // ustala wektor z pociskami
	FloatRect getBounds();
	void setTankPosition(Vector2f _position);

	FloatRect copySpriteRotation(bool tankOne); // ustawia kopie sprajta i zwraca jego boundsy podczas obrotów
												//argument sprawdza o ktory czolg chodzi (osobne sterowanie dla pierwszego i drugiego)
	FloatRect tankForwardAndBackward(bool tankOne); // ustawia kopie sprajta w przód lub ty³. 
													//argument sprawdza o ktory czolg chodzi (osobne sterowanie dla pierwszego i drugiego)
	void assignRotation();	// ustawienie rotacji sprajta jako przypisanie do niego kopii która nie kolidowa³a
};