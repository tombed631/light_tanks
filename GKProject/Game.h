#ifndef Game_hpp
#define Game_hpp
#endif

#include "Includes.h"
#include "Player.h"
#include "Wall.h"
#include "Collision.h"
/*Klasa uruchomieniowa gry*/
class Game
{
private:
	Player *playerOne, *playerTwo; // deklaracja obu graczy
	Event eventHandle; //handle events
	bool isRunningGame; // czy gra jest uruchomiana
	vector <Player*> players; // wektor ze wskaznikami na obiekt graczy
	vector <Wall*> walls;
	Wall *wall;
	FloatRect x, y, z;
public:
	Game();
	void run(RenderWindow &window); // odpala g³ówn¹ petle gry
	void engine(RenderWindow &window); // silnik gry odpowiedzialny za ruch pojazdów, pocisków i kolizje
	void moveTankOne(); // najpierw przesuwamy kopie sprajta - jezeli bedzie kolidowa³o z ktoryms z obiektow nie przypiszemy nowej pozycji
						// oryginalnemu, jesli nie bedzie to przypisujemy nowa pozycje. efekt kolizji zachowany
	void moveTankTwo(); // to samo jak wyzej

};