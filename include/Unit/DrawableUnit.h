#ifndef CLASSES_UNITS_DRAWABLEUNIT_H_
#define CLASSES_UNITS_DRAWABLEUNIT_H_

#include <map>
#include <string>

#include "../Drawing/FrameManager.h"
#include "Unit.h"

class DrawableUnit : public Unit{
public:
	DrawableUnit();
	DrawableUnit(double,double,double,double);
	DrawableUnit(std::string,double,double,double,double);
	void addFrameMgr(std::string,FrameManager);
	std::map<std::string,FrameManager> getFrameMgrMap();
	FrameManager* getFrameMgrFromMap(std::string);
	FrameManager* getFrameMgrFromCurAction();
	void animate();
	void move();
private:
	std::map<std::string,FrameManager> frameMgrMap;
};
#endif
