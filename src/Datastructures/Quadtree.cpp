#include "../../include/Datastructures/Quadtree.h"
#include <cstdio>

Quadtree::Quadtree(int cLevel, SDL_Rect bounds) {
	this->bounds = bounds;
	this->level = cLevel;
	//printf("\n%d\n", level);
}

void Quadtree::clear() {
	this->objects.clear();
	for (unsigned int i = 0; i < this->nodes.size(); i++) {
		this->nodes.at(i).clear();
	}
}

void Quadtree::split() {
	SDL_Rect r;
	r.x = this->bounds.x; //top-left
	r.x = this->bounds.y;
	r.w = this->bounds.w / 2;
	r.h = this->bounds.h / 2;
	this->nodes.push_back(Quadtree(level + 1, r));
	r.x = this->bounds.x + (this->bounds.w / 2); //top-right
	this->nodes.push_back(Quadtree(level + 1, r));
	r.x = this->bounds.x; //bot-left
	r.y = this->bounds.y + (this->bounds.h / 2);
	this->nodes.push_back(Quadtree(level + 1, r));
	r.x = this->bounds.x + (this->bounds.w / 2); //bot-right
	this->nodes.push_back(Quadtree(level + 1, r));
}

int Quadtree::getIndex(Unit u) {
//gets the index of (1,2,3,4 aka top-left,top-right,bot-left,bot-right)
	int returnIndex = -1;
	SDL_Rect r;
	r.x = u.xPos;
	r.y = u.yPos;
	r.w = u.getWidth();
	r.h = u.getHeight();
	double horizontalMid = (double) this->bounds.x + (double) (this->bounds.w / 2);
	double verticalMid = (double) this->bounds.y + (double) (this->bounds.h / 2);
	if (r.x < horizontalMid) { //left
		if (r.y < verticalMid) { //top
			returnIndex = 0;
		} else if (r.y > verticalMid) { //bot
			returnIndex = 2;
		}
	} else if (r.x > horizontalMid) { //right
		if (r.y < verticalMid) { //top
			returnIndex = 1;
		} else if (r.y > verticalMid) { //bot
			returnIndex = 3;
		}
	}
	return returnIndex;
}


void Quadtree::insert(Unit u) {
	if(!nodes.empty()){
		int index = getIndex(u);

		if(index != -1){
			nodes[index].insert(u);
			return;
		}
	}

	objects.push_back(u);

	if(objects.size() > MAX_NODE_OBJ && level < MAX_LEVELS){
		if(nodes.empty()){
			split();
		}

		int i = 0;
		while(i < objects.size()){
			int index = getIndex(objects[i]);
			if(index != -1){
				nodes[index].insert(objects[i]);
				objects.erase(objects.begin() + i);
			} else {
				i++;
			}
		}

	}

}
std::vector<Unit> Quadtree::retriveLocalUnits(Unit u, std::vector<Unit>* uList) {
//retrives the units local to u
//uList contains the units needed to be checked
	//get the nodes in the appropriate sublevels
	int i = getIndex(u);
	if (i != -1 && !nodes.empty()) {
		nodes[i].retriveLocalUnits(u, uList);
	}
	//add the nodes of the current level
	std::vector<Unit>::iterator objectIter = objects.begin();
	while (objectIter != objects.end()) {
		uList->push_back(*objectIter);
		objectIter++;
	}

	return *uList;

}

void Quadtree::countAndPrint(Quadtree t) {
	printf("\n");
	if (t.nodes.size() > 0) {
		for (int i = 0; i < level; i++) {
			printf("+");
		}
		printf("%d : %d objects in node. has %d children\n", t.level,
				t.objects.size(), t.nodes.size());
		for (int i = 0; i < t.nodes.size(); i++) {
			countAndPrint(t.nodes[i]);
		}
	} else {
		for (int i = 0; i < level; i++) {
			printf("+");
		}
		printf("%d : Last node containing %d objects\n", t.level,
				t.objects.size());
	}
}
