#ifndef Help_hpp
#define Help_hpp


#include "Includes.h"

class Help
{
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

	bool showHelp(RenderWindow &window, p3d::PlTankColors colors );

};

#endif