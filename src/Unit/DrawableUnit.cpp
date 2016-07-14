#include "../../include/Unit/DrawableUnit.h"

#include <cstdio>
#include <utility>

DrawableUnit::DrawableUnit(std::string name, double x,double y,double w,double h) : Unit(name,x,y,w,h){

}

std::map<std::string,FrameManager> DrawableUnit::getFrameMgrMap(){
	return frameMgrMap;
}

void DrawableUnit::addFrameMgr(std::string key, FrameManager frameMgr){
	frameMgrMap.insert(std::pair<std::string,FrameManager>(key,frameMgr));
}

FrameManager* DrawableUnit::getFrameMgrFromMap(std::string s){
	FrameManager* f = &frameMgrMap.at(s);
	return f;
}

FrameManager* DrawableUnit::getFrameMgrFromCurAction(){
	FrameManager* f = getFrameMgrFromMap(this->getAction());
	return f;
}

void DrawableUnit::animate(){
	//printf("animating image : %s\n",this->getAction().c_str());
	this->getFrameMgrFromMap(this->getAction())->incrementFrame();
}

void DrawableUnit::move(){
	Unit::move();
	animate();
}
