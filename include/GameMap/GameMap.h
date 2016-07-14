#ifndef CLASSES_MAP_MAP_H_
#define CLASSES_MAP_MAP_H_

#include <map>
#include <string>
#include <vector>

#include "../Datastructures/Quadtree.h"
#include "../Drawing/FrameManager.h"
#include "../Drawing/ImageFactory.h"
#include "../Event/EventHandler.h"
#include "../Event/KeyboardEvent.h"
#include "../GameMap/Tile.h"
#include "../Unit/NPC.h"
#include "../Unit/Player.h"

class GameMap {
public:
	GameMap();
	int getWidth();
	int getHeight();
	void setWidth(int);
	void setHeight(int);
	void addUnitToMap(std::string, DrawableUnit);
	std::map<std::string,DrawableUnit>* getAllUnits();
	DrawableUnit* getUnitByName(std::string);
	std::vector<Tile>* getAllTiles();
	bool isCollision(Unit, Unit);
	Quadtree* collisionTree;
private:
	int width;
	int height;
	std::map<std::string,DrawableUnit> units;
	std::vector<Tile> tiles;

};

#endif
