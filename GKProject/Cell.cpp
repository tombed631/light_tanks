#include "Cell.h"

void Cell::setBottom(Wall *wall){
	bottom = wall;
};

void Cell::setRight(Wall *wall){
	right = wall;
};

Wall *Cell::getBottom(){
	return bottom;
};
Wall *Cell::getRight(){
	return right;
};