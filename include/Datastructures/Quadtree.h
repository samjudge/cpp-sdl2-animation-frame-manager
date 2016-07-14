#ifndef SRC_DATASTRUCTURES_QUADTREE_H_
#define SRC_DATASTRUCTURES_QUADTREE_H_

#include <SDL2/SDL_rect.h>
#include <vector>

#include "../Unit/Unit.h"

class Quadtree {
public:
	Quadtree(int cLevel, SDL_Rect bounds);
	void clear();
	void split();
	void insert(Unit);
	std::vector<Unit> retriveLocalUnits(Unit, std::vector<Unit>*);
	void countAndPrint(Quadtree);
private:
	int getIndex(Unit);
	int getIndexBIG(Unit);
	static const int MAX_NODE_OBJ = 8;
	static const int MAX_LEVELS = 5;

	int level;
	SDL_Rect bounds;
	std::vector<Unit> objects;
	std::vector<Quadtree> nodes;
};
#endif
