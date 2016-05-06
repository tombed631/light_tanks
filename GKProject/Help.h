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
	vector <Sprite> imagesVector;
	Sprite arrowKeysSprite, wsadKeysSprite, spaceKeySprite, pKeySprite;
	Texture arrowKeysTexture, wsadKeysTexture, spaceKeyTexture, pKeyTexture;
public:
	/*Constructor*/
	Help();
	/*Shows Menu in window */
	bool showHelp(RenderWindow &window);
};