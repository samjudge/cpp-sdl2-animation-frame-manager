#ifndef CLASSES_UNITS_PLAYER_H_
#define CLASSES_UNITS_PLAYER_H_

#include "DrawableUnit.h"

class Player : public DrawableUnit {
public:
	Player();
	Player(double,double,double,double);
	Player(std::string, double, double, double, double);

	void move();

	void moveUpEvent();
	void moveDownEvent();
	void moveLeftEvent();
	void moveRightEvent();
	void releaseUpEvent();
	void releaseDownEvent();
	void releaseLeftEvent();
	void releaseRightEvent();
private:
};


#endif
