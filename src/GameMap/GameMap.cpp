#include "../../include/GameMap/GameMap.h"
#include <cstdio>
#include <string.h>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <ctime>
#include "../../tinyxml/tinyxml.h"

GameMap::GameMap(){
	width = 100;
	height = 100;

	//Quadtree for broad phase collision detection
	SDL_Rect r;
	r.w = 640;
	r.h = 640;
	r.x = 0;
	r.y = 0;

	collisionTree = new Quadtree(0,r);


	//The below will be loaded in from external XML files as required (eventually)

	ImageFactory* imgFact = ImageFactory::getInstance();

	FrameManager mudWallTiles;
	mudWallTiles.setFrameX(128);
	mudWallTiles.setFrameY(320);
	mudWallTiles.setFrameW(64);
	mudWallTiles.setFrameH(64);
	mudWallTiles.setFrameMax(0);
	mudWallTiles.setFrameCur(0);
	mudWallTiles.setFrameOffsetX(0);
	mudWallTiles.setFrameOffsetY(0);
	imgFact->addSpriteSheet(mudWallTiles,"../resources/wall.bmp","wall","wall-single");


	//loading in the frames for a player - just a test for tinyXML
	TiXmlDocument doc("../resources/units.xml");
	printf("Trying to load...");
	if(doc.LoadFile()){
		printf("Doc loaded");
		TiXmlElement* node = doc.FirstChildElement("unit");
		while(node != NULL){
			Player* unit = new Player(std::string("player"),0,0,64,64);
			unit->setAction("idle-down");
			std::string name = node->Attribute("name");
			TiXmlElement* frameNode = node->FirstChildElement("actionAnimation");
			while(frameNode != NULL ){
				std::string action = frameNode->Attribute("name");
				std::string imgsrc = frameNode->FirstChildElement("imagesrc")->FirstChild()->Value();
				printf("%s",imgsrc.c_str());
				FrameManager frameMgr;
				frameMgr.setFrameX(atoi(frameNode->FirstChildElement("imgSourceX")->FirstChild()->Value()));
				frameMgr.setFrameY(atoi(frameNode->FirstChildElement("imgSourceY")->FirstChild()->Value()));
				frameMgr.setFrameW(atoi(frameNode->FirstChildElement("frameWidth")->FirstChild()->Value()));
				frameMgr.setFrameH(atoi(frameNode->FirstChildElement("frameHeight")->FirstChild()->Value()));
				frameMgr.setFrameMax(atoi(frameNode->FirstChildElement("frameMax")->FirstChild()->Value()));
				frameMgr.setFrameCur(0);
				frameMgr.setFrameOffsetX(atoi(frameNode->FirstChildElement("frameOffsetX")->FirstChild()->Value()));
				frameMgr.setFrameOffsetY(atoi(frameNode->FirstChildElement("frameOffsetY")->FirstChild()->Value()));
				std::string s2 = "../resources/"+imgsrc;
				printf("LOADING FROM %s\n",s2.c_str());
				imgFact->addSpriteSheet(frameMgr,"../resources/"+imgsrc,name,action);
				unit->addFrameMgr(action,frameMgr);

				frameNode = frameNode->NextSiblingElement();

			}
			std::string s = "player";
			printf("INSERTING PLAYER");
			units.insert(std::pair<std::string,Player>(s,*unit));
			delete unit;
			node = node->NextSiblingElement();
		}
	} else {
		std::cout << doc.ErrorDesc() << std::endl;
		std::cout << doc.ErrorRow() << std::endl;
		std::cout << doc.ErrorCol() << std::endl;
	}
	//end test
	//std::srand(std::time(0));
	for(int x = 1; x <= 640; x+=64){
		for(int y = 1; y <= 640; y+=64){
			if((x >= 1 && y >= 1) && (x <= 640 && y <= 640)){
				//if(rand()%6 == 0){
					Tile *t = new Tile("wall",x,y,72,72);
					t->setAction("wall-single");
					t->addFrameMgr("wall-single",mudWallTiles);
					t->xPos = x;
					t->yPos = y;
					tiles.push_back(*t);
				//}
			}
		}
	}

	//adding all tiles and units to the quadtree (must be updated regularly - i.e. whenever something moves)
	for (std::vector<Tile>::iterator tileIter = tiles.begin(); tileIter != tiles.end(); tileIter++){
		printf("NEW INSERT!!!\n");
		this->collisionTree->insert(*tileIter);
	}
	collisionTree->countAndPrint(*collisionTree);

}

bool GameMap::isCollision(Unit u1, Unit u2){
	if(	u1.xPos < u2.xPos + u2.getWidth() &&
		u1.xPos + u1.getWidth() > u2.xPos &&
		u1.yPos < u2.yPos + u2.getHeight() &&
		u1.yPos + u1.getHeight() > u2.yPos){
		return true;
	}
	return false;
}

int GameMap::getWidth(){
	return width;
}

int GameMap::getHeight(){
	return height;
}

void GameMap::setWidth(int width){
	this->width = width;
}

void GameMap::setHeight(int height){
	this->height = height;
}

void GameMap::addUnitToMap(std::string s, DrawableUnit u){
	units.insert(std::pair<std::string, DrawableUnit>(s,u));
}

std::map<std::string, DrawableUnit>* GameMap::getAllUnits(){
	return &units;
}

std::vector<Tile>* GameMap::getAllTiles(){
	return &tiles;
}

DrawableUnit* GameMap::getUnitByName(std::string s){
	return &this->units.at(s);
}
