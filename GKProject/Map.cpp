#include "Map.h"

void Map::draw(RenderTarget &target, RenderStates states) const
{
	for (unsigned int i = 0; i < walls.size(); i++)
		target.draw(*walls[i]);
};

void Map::createMap(RenderWindow &gameWindow){
	windowX = gameWindow.getSize().x;
	windowY = gameWindow.getSize().y;
	ifstream mapFile;
	string fileData;
	int cellInfo;
	mapFile.open("Maps\\Map1.txt", ios::in);
	if (mapFile.good() == false){
		MessageBox(NULL, "Brak shematu mapy!", "ERROR", NULL);
		return;
	}
	//ramka okna
	walls.push_back(new Wall(10, windowX, Vector2f(0, 0), 0));
	walls.push_back(new Wall(10, windowX, Vector2f(0, windowY - 10), 0));
	walls.push_back(new Wall(windowY, 10, Vector2f(0, 0), 0));
	walls.push_back(new Wall(windowY, 10, Vector2f(windowX - 10, 0), 0));

	for (int y = 0; y < 7; y++){
		for (int x = 0; x < 9; x++){
			//getline(mapFile, fileData);
			mapFile >> fileData;
			cellInfo = atoi(fileData.c_str());
			switch (cellInfo){
			case 0:
				break;

			case 1:
				mapCells[y][x] = new Cell();
				mapCells[y][x]->setBottom(new Wall(10, 90, Vector2f(((x + 1) * 90) - 80, (y + 1) * 90), 0));
				walls.push_back(mapCells[y][x]->getBottom());
				break;

			case 2:
				mapCells[y][x] = new Cell();
				mapCells[y][x]->setRight(new Wall(90, 10, Vector2f((x + 1) * 90, ((y + 1) * 90) - 80), 0));
				walls.push_back(mapCells[y][x]->getRight());
				break;

			case 3:
				mapCells[y][x] = new Cell();
				mapCells[y][x]->setBottom(new Wall(10, 90, Vector2f(((x + 1) * 90) - 80, (y + 1) * 90), 0));
				walls.push_back(mapCells[y][x]->getBottom());
				mapCells[y][x]->setRight(new Wall(90, 10, Vector2f((x + 1) * 90, ((y + 1) * 90) - 80), 0));
				walls.push_back(mapCells[y][x]->getRight());
				break;
			}
		}
	}
	
	mapFile.close();
};

int Map::getWallsSize(){
	return walls.size();
};

Wall* Map::getWall(int index){
	return walls[index];
};

FloatRect Map::getWallBounds(int index){
	return walls[index]->getBounds();
};