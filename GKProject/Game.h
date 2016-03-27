#ifndef Game_hpp
#define Game_hpp
#endif

#include "Includes.h"
#include "Player.h"

/*Klasa uruchomieniowa gry*/
class Game
{
private:
	Player *playerOne, *playerTwo; // deklaracja obu graczy
	Event eventHandle; //handle events
	bool isRunningGame; // czy gra jest uruchomiana
	vector <Player*> players; // wektor ze wskaznikami na obiekt graczy
public:
	Game();
	void run(RenderWindow &window);



};