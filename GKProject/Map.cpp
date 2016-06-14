#include "Map.h"

void Map::draw(RenderTarget &target, RenderStates states) const
{
	for (unsigned int i = 0; i < walls.size(); i++)
		target.draw(*walls[i]);
};

void Map::createMap(RenderWindow &gameWindow){
	windowX = (float)gameWindow.getSize().x;
	windowY = (float)gameWindow.getSize().y - 120;
	ifstream mapFile;
	string fileData;
	int cellInfo;
	string mapPath = "Maps\\";
	int chooseMap = std::rand() % 5;
	switch (chooseMap)
	{
	case 0:
		mapPath += "Map1.txt";
		break;
	case 1:
		mapPath += "Map2.txt";
		break;
	case 2:
		mapPath += "Map3.txt";
		break;
	case 3:
		mapPath += "Map4.txt";
		break;
	case 4:
		mapPath += "Map5.txt";
		break;
	}
	mapFile.open(mapPath, ios::in);
	if (mapFile.good() == false){
		MessageBox(NULL, "No schema of map!", "ERROR", NULL);
		isDone = false;
		return;
	}
	//ramka okna bazowa dla ka¿dego
	walls.push_back(new Wall(10.f, windowX, Vector2f(0.f, 0.f), 0));
	walls.push_back(new Wall(10.f, windowX, Vector2f(0.f, windowY - 10), 0));
	walls.push_back(new Wall(windowY, 10.f, Vector2f(0.f, 0.f), 0));
	walls.push_back(new Wall(windowY, 10.f, Vector2f(windowX - 10, 0.f), 0));

	// wczytywanie danych mapy z plików
	// okno dzielone na kratki 9 kolumn, 7 wierszy
	for (int y = 0; y < 7; y++){
		for (int x = 0; x < 9; x++){
			// wczytywanie z pliku
			mapFile >> fileData;
			cellInfo = atoi(fileData.c_str());
			switch (cellInfo){
				//0 nie ma nic
			case 0:
				break;

				// 1 pozioma sciana
			case 1:
				// tworzy obiekt kratki w tablicy
				mapCells[y][x] = new Cell();
				// ustawia zmienna odpowiednimi wartosciami wyliczanymi ze schematu
				mapCells[y][x]->setBottom(new Wall(10.f, 100.f, Vector2f(((x + 1) * 90.f) - 90.f, (y + 1) * 90.f), 0));
				// puszuje do wektora stworzona sciane
				walls.push_back(mapCells[y][x]->getBottom());
				break;

				// 2 pionowa sciana
			case 2:
				mapCells[y][x] = new Cell();
				mapCells[y][x]->setRight(new Wall(100.f, 10.f, Vector2f((x + 1) * 90.f, ((y + 1) * 90.f) - 90.f), 0));
				walls.push_back(mapCells[y][x]->getRight());
				break;

				// 3 obie sciany
			case 3:
				mapCells[y][x] = new Cell();
				mapCells[y][x]->setBottom(new Wall(10.f, 100.f, Vector2f(((x + 1) * 90.f) - 90.f, (y + 1) * 90.f), 0));
				walls.push_back(mapCells[y][x]->getBottom());
				mapCells[y][x]->setRight(new Wall(100.f, 10.f, Vector2f((x + 1) * 90.f, ((y + 1) * 90.f) - 90.f), 0));
				walls.push_back(mapCells[y][x]->getRight());
				break;
			}
		}
	}

	mapFile.close();
	isDone = true;
};

int Map::getWallsSize(){
	return walls.size();
};

Wall* Map::getWall(int index){
	return walls[index];
};

const RectangleShape Map::getWallShape(int index){
	return walls[index]->getShape();
};

Map::~Map() {
	for (vector <Wall*>::iterator i = walls.begin(); i != walls.end(); i++)
		if ((*i) != nullptr)
			delete (*i);

	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 9; j++)
			if (mapCells[i][j] != nullptr)
				delete mapCells[i][j];
}