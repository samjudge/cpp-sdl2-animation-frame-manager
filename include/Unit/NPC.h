#ifndef CLASSES_UNITS_NPC_H_
#define CLASSES_UNITS_NPC_H_

#include <string>

#include "DrawableUnit.h"

class NPC : public DrawableUnit {
public:
	NPC();
	NPC(double,double,double,double);
	NPC(std::string, double, double, double, double);
private:
};

#endif
