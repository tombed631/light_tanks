#ifndef Player_hpp
#define Player_hpp
#endif

#include "Includes.h"
#include "Bullet.h"
#include "ParticleSystem.h"

/*Klasa reprezentujaca gracza*/
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
	vector <Bullet*> bullets; // tablica z pociskami
	int points;					// punkty gracza
	ParticleSystem *bulletExplosion;
public:
	bool isHited; // czy zosta³ trafiony
	Player();
	virtual void draw(RenderTarget &target, RenderStates states) const; // wirtualna metoda pozwalajaca rysowac obiekt
	Player(String _name, String path, Vector3i colors); //konstruktor z argumentamii
	String getName(); // zwraca nazwe zawodnika
	void moveTank(); // porusza czo³giem gracza - przypisuje oryginalnego sprajta do jego kopii - jesli nie by³o kolizji
	Vector2f getTankPosition(); //zwraca pozycje czo³gu
	void bulletShoot(); // nastapil strzal - tworzenie pocisku 
	vector <Bullet*> getBullets(); // zwraca wektor z pociskami
	void deleteBullets();
	Bullet* getSingleBullet(int i);	//zwraca pojedynczy pocisk 
	CircleShape getBulletsShape(int i);	// zwraca kszta³t pocisku
	void setBullets(vector <Bullet*> v); // ustala wektor z pociskami
	FloatRect getBounds();					
	void setTankPosition(Vector2f _position); // ustawia pozycje czo³gu
	const Sprite getSprite();				// zwraca sprite czo³gu
	Sprite copySpriteRotation(bool tankOne); // ustawia kopie sprajta i zwraca jego boundsy podczas obrotów
										//argument sprawdza o ktory czolg chodzi (osobne sterowanie dla pierwszego i drugiego)
	Sprite tankForwardAndBackward(bool tankOne); // ustawia kopie sprajta w przód lub ty³. 
													//argument sprawdza o ktory czolg chodzi (osobne sterowanie dla pierwszego i drugiego)
	void assignRotation();	// ustawienie rotacji sprajta jako przypisanie do niego kopii która nie kolidowa³a
	bool isMoving();
	bool isRotation();
	int getPoints();
	void setPoints(int _points);
	void setPlayerRotation(float rotation);
	void setEmiter(Bullet *bullet);
	ParticleSystem *getBulletExplosion();

};