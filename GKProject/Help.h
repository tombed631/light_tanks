#ifndef Help_hpp
#define Help_hpp
#endif

#include "Includes.h"

class Help
{
private:
private:
	Event eventHandle; //handle events
	bool isRunningHelp; // is app running? 
	Font font;
	vector <Text> textsVector;
	vector <Sprite> imagesVector;
public:
	/*Constructor*/
	Help();
	/*Shows Menu in window */
	bool showHelp(RenderWindow &window);
	/*Load font from file*/
	void loadFont();
	float middlePosition(Text object);

};