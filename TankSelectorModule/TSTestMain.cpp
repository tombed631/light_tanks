
/*		Entry for Tank Selector Test		*/

#include "TankSelector.h"
#include "SFML\Graphics.hpp"


int main(void){

	//create a sfml window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TankSelector");

	//launch tank selector and capture the result
	try{
		PlTankTypes playersTanks = TankSelector(window).run();
	}
	catch (GLEWInitError & e){
		return 1;
	}
	catch (ShaderCompileError & e){
#ifdef _DEBUG
		std::cout << e.what() << std::endl;
		system("pause");
#endif
		return 1;
	}
	catch (LoadModelError & e){
#ifdef _DEBUG
		std::cout << e.what() << std::endl;
		system("pause");
#endif
		return 1;
	}

	return 0;
}