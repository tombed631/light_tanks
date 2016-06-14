#ifndef Map_hpp
#define Map_hpp

#include "Includes.h"
#include "Cell.h"

class Map : public Drawable, public Transformable
{
private:
	//Wall *wall;
	vector <Wall*> walls;
	float windowX, windowY;
	Cell *mapCells[7][9];

public:

	bool isDone;
	virtual ~Map();
	Map(){};

	void createMap(RenderWindow &gameWindow);
	int getWallsSize();
	Wall * getWall(int index);
	const RectangleShape getWallShape(int index);

	virtual void draw(RenderTarget &target, RenderStates states) const; // wirtualna metoda pozwalajaca rysowac obiekt
};

#endif