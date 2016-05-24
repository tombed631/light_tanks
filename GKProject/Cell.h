#ifndef Cell_hpp
#define Cell_hpp


#include "Includes.h"
#include "Wall.h"

class Cell 
{
private:
	Wall *bottom;
	Wall *right;
public:
	

	bool visited = false;

	void setBottom(Wall *wall);
	void setRight(Wall *wall);

	Wall *getBottom();
	Wall *getRight();
};

#endif