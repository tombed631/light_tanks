
/*		Entry for Tank Selector Test		*/

#include "TankSelector.h"
#include "SFML\Graphics.hpp"


int main(void){

	//create a sfml window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TankSelector");

	//launch tank selector and capture the result
	PlTankTypes playersTanks = TankSelector(window).run();


	return 0;
}