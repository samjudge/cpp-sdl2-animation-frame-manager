#ifndef CLASSES_MAP_TILE_H_
#define CLASSES_MAP_TILE_H_

#include <string>

#include "../Unit/DrawableUnit.h"

class Tile : public DrawableUnit{
public:
	Tile(std::string s, double x,double y,double w,double h);
};

#endif
