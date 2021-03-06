#ifndef Game_hpp
#define Game_hpp


#include "Includes.h"
#include "Player.h"
#include "Collision.h"
#include "Map.h"

/*Klasa uruchomieniowa gry*/
class Game
{
private:
	Player *playerOne, *playerTwo; // deklaracja obu graczy
	Map *map;
	Event eventHandle; //handle events

	bool wasCollisionRotation,wasCollisionMove;
	vector <Player*> players; // wektor ze wskaznikami na obiekt graczy
	Collision col;				// collision object
	Time timeToRestart; // czas zycia 
	Clock clock; // zegar generujacy czas
	Text playerOnePoints, playerTwoPoints, pointTitle; // punktacja
	Sound destroySound, shootSound, ricochetSound; // zmienne dzwiekow
	SoundBuffer destroySoundBuffer, shootSoundBuffer, ricochetSoundBuffer; // buffery dzwiekow
	vector <ParticleSystem*> explosions;
	ParticleSystem *firstTankExplosions, *secondTankExplosions, *bulletExplosion, *firstPointChanging, *secondPointChanging;
	Texture scoreBoardTankTextureOne, scoreBoardTankTextureTwo;
	Sprite scoreBoardTankSpriteOne, scoreBoardTankSpriteTwo;

public:
	bool isRunningGame; // czy gra jest uruchomiana

	Game(RenderWindow &window);
	virtual ~Game();
	bool run(RenderWindow &window, p3d::PlTankColors playerColors, string playerOneName, string playerTwoName); // odpala g��wn� petle gry
	void engine(RenderWindow &window); // silnik gry odpowiedzialny za ruch pojazd�w, pocisk�w i kolizje

	void reset();
	// najpierw przesuwamy kopie sprajta - jezeli bedzie kolidowa�o z ktoryms z obiektow nie przypiszemy nowej pozycji
	// oryginalnemu, jesli nie bedzie to przypisujemy nowa pozycje. efekt kolizji zachowany
	void moveTank(Player *playerMain, Player *playerSub,bool which); 
	void bulletsEngine(RenderWindow &window, Player *player); // fizyka pociskow gracza pierwszego
	void detectBulletsCollision(Player *player);	// pociski kolidujace ze scianami zmieniaja swoj kierunek(gracz pierwszy)
	bool isPlayerHit(Player *player, Bullet *bullet);
	void playerHited(Player *player);
	void finalResults(RenderWindow &window, Player *playerOne, Player *playerTwo);
};

#endif