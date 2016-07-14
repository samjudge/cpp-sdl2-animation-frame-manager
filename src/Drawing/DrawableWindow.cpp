#include "../../include/Drawing/DrawableWindow.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <cstdio>
#include <iterator>
#include <map>
#include <string>
#include <vector>

#include "../../include/Drawing/FrameManager.h"
#include "../../include/GameMap/Tile.h"


DrawableWindow* DrawableWindow::instance;

DrawableWindow::DrawableWindow(){
	this->window = SDL_CreateWindow(
			"Tower Of Orgon",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			640,
			640,
			0);
	this->renderer = SDL_CreateRenderer(window,-1,0);
	this->imgFact = ImageFactory::getInstance();

}

DrawableWindow* DrawableWindow::getInstance(){
	if(instance == NULL){
		instance = new DrawableWindow();
	}
	return instance;
}

void DrawableWindow::drawBitmap(SDL_Surface* bmp, SDL_Rect* dst){
	SDL_SetColorKey(bmp, SDL_TRUE, 0xFD4DD3);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(
			this->renderer,
			bmp);
	SDL_RenderCopy(this->renderer, texture, NULL, dst);
	SDL_DestroyTexture(texture);
}

void DrawableWindow::drawScreen(){
	SDL_RenderPresent(this->renderer);
	SDL_RenderClear(this->renderer);
}

void DrawableWindow::renderMap(GameMap m){ //this logic needs to be moved to map
	std::map<std::string, DrawableUnit> units = *m.getAllUnits();
	std::map<std::string, DrawableUnit>::iterator unitsIter = units.begin();
	SDL_Rect* dstRect = new SDL_Rect();
	std::vector<Tile> tiles = *m.getAllTiles();
	std::vector<Tile>::iterator tileIter = tiles.begin();
	while(tileIter != tiles.end()){
		Tile t = *tileIter;
		dstRect->x = t.getXPos();//-(int)(t.getFrameMgrFromMap(t.getAction())->getFrameW());
		dstRect->y = t.getYPos();//-(int)(t.getFrameMgrFromMap(t.getAction())->getFrameH());
		dstRect->w = t.getWidth();
		dstRect->h = t.getHeight();
		SDL_Surface* img = this->imgFact->getSubImage("wall",t.getAction(),t.getFrameMgrFromMap(t.getAction()));
		this->drawBitmap(img,dstRect);
		SDL_FreeSurface(img);
		++tileIter;
	}
	//TEST
	unitsIter = units.begin();
	std::vector<Unit> localList;
	while(unitsIter != units.end()){
		localList = m.collisionTree->retriveLocalUnits(unitsIter->second,&localList);
		//printf("!!!!!!!!!!!!!!!!!!!!!!checking %d / %d tiles\n",localList.size(),tiles.size());
		std::vector<Unit>::iterator localIter = localList.begin();
		while(localIter != localList.end()){
			if(m.isCollision(unitsIter->second,*localIter)){
				SDL_Rect* r = new SDL_Rect;
				r->x = localIter->xPos;
				r->y = localIter->yPos;
				r->w = localIter->getWidth();
				r->h = localIter->getHeight();
				SDL_Surface *testSurf = SDL_CreateRGBSurface(0,r->w,r->h, 32,0,0,0,0);
				SDL_FillRect(testSurf,NULL,SDL_MapRGB(testSurf->format, 255,0,0));
				this->drawBitmap(testSurf,r);
				SDL_FreeSurface(testSurf);
			} else {
				SDL_Rect* r = new SDL_Rect;
				r->x = localIter->xPos;
				r->y = localIter->yPos;
				r->w = localIter->getWidth();
				r->h = localIter->getHeight();
				SDL_Surface *testSurf = SDL_CreateRGBSurface(0,r->w,r->h, 32,0,0,0,0);
				SDL_FillRect(testSurf,NULL,SDL_MapRGB(testSurf->format, 0,255,255));
				this->drawBitmap(testSurf,r);
				SDL_FreeSurface(testSurf);
			}
			localIter++;
		}
		//printf("%d\n",x);
		unitsIter++;
	}

	//printf("!!!!!!!!!!!!!!!!!!!!!!checking %d / %d tiles\n",localList.size(),tiles.size());
	/*tileIter = tiles.begin();
	while(tileIter != tiles.end()){
		localList.clear();
		//printf("!!!!!!!!!!!!!OLLA BOYS!!!!!!!!!!!!!!!!!!!!!!");
		Unit u = *tileIter;
		//printf("x%d : y%d : w%d : h%d\n",x,y,w,h);
		localList = m.collisionTree->retriveLocalUnits(u,&localList);
		//printf("¬checking %d / %d tiles\n",localList.size(),tiles.size());
		std::vector<Unit>::iterator localIter = localList.begin();
		while(localIter != localList.end()){
			if(m.isCollision(*tileIter,*localIter)){
				//printf("!");
			}
			localIter++;
		}
		//printf("%d\n",x);
		tileIter++;
	}*/

	//END TEST
	unitsIter = units.begin();
	while(unitsIter != units.end()){
		DrawableUnit u = unitsIter->second;
		dstRect->x = u.getXPos();//-(int)(u.getFrameMgrFromMap(u.getAction())->getFrameW()/2);
		dstRect->y = u.getYPos();//-(int)(u.getFrameMgrFromMap(u.getAction())->getFrameH()/2);
		dstRect->w = u.getWidth();
		dstRect->h = u.getHeight();
		//printf("%d : %d\n", dstRect->x,dstRect->y);
		SDL_Surface* img = this->imgFact->getSubImage(u.getName(),u.getAction(),u.getFrameMgrFromMap(u.getAction()));
		//printf("%s : %s\n", u.getName().c_str(), u.getAction().c_str());
		//SDL_Surface *img = SDL_CreateRGBSurface(0,20,20, 32,0,0,0,0);
		//SDL_FillRect(img,NULL,SDL_MapRGB(img->format, 0,255,0));
		this->drawBitmap(img,dstRect);
		SDL_FreeSurface(img);
		++unitsIter;
	}




}
