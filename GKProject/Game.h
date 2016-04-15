#ifndef Game_hpp
#define Game_hpp
#endif

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
	bool isRunningGame; // czy gra jest uruchomiana
	vector <Player*> players; // wektor ze wskaznikami na obiekt graczy
	Collision col;				// collision object
	Time timeToRestart; // czas zycia 
	Clock clock; // zegar generujacy czas
	Text playerOnePoints, playerTwoPoints, pointTitle; // punktacja
	Font font;
	Sound destroySound, shootSound, ricochetSound; // zmienne dzwiekow
	SoundBuffer destroySoundBuffer, shootSoundBuffer, ricochetSoundBuffer; // buffery dzwiekow
	vector <ParticleSystem*> explosions;
	ParticleSystem *firstTankExplosions, *secondTankExplosions, *bulletExplosion, *firstPointChanging, *secondPointChanging;


public:
	Game(RenderWindow &window);
	bool run(RenderWindow &window); // odpala g³ówn¹ petle gry
	void engine(RenderWindow &window); // silnik gry odpowiedzialny za ruch pojazdów, pocisków i kolizje

	void reset();
	// najpierw przesuwamy kopie sprajta - jezeli bedzie kolidowa³o z ktoryms z obiektow nie przypiszemy nowej pozycji
	// oryginalnemu, jesli nie bedzie to przypisujemy nowa pozycje. efekt kolizji zachowany
	void moveTank(Player *playerMain, Player *playerSub,bool which); 
	void bulletsEngine(RenderWindow &window, Player *player); // fizyka pociskow gracza pierwszego
	void detectBulletsCollision(Player *player);	// pociski kolidujace ze scianami zmieniaja swoj kierunek(gracz pierwszy)
	bool isPlayerHit(Player *player, Bullet *bullet);
	void playerHited(Player *player);
};