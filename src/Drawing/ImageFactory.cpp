#include "../../include/Drawing/ImageFactory.h"

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <cstdio>
#include <utility>

std::map<std::string, std::map<std::string, SDL_Surface> > ImageFactory::spritesheets;
ImageFactory* ImageFactory::instance;

ImageFactory::ImageFactory() {
	spritesheets.clear();
}

ImageFactory* ImageFactory::getInstance(){
	if(instance == NULL){
		instance = new ImageFactory();
	}
	return instance;
}

SDL_Surface* ImageFactory::loadSpriteSheetAsSurface(std::string path){
	return SDL_LoadBMP(path.c_str());
}

SDL_Surface* ImageFactory::loadPartialSprieSheetAsSurface(std::string path, SDL_Rect* src){
	SDL_Surface* pSurface = loadSpriteSheetAsSurface(path);
	SDL_Surface* cSurface = SDL_CreateRGBSurface(0,src->w,src->h,32,0,0,0,0);
	SDL_BlitSurface(pSurface,src,cSurface,NULL);
	delete pSurface;
	return cSurface;
}

void ImageFactory::addSpriteSheet(FrameManager framesInfo, std::string path, std::string spritename, std::string spriteaction){
	SDL_Rect* imgInfo = new SDL_Rect();
	printf("adding %s\n",path.c_str());
	imgInfo->x = framesInfo.getFrameX();
	imgInfo->y = framesInfo.getFrameY();
	imgInfo->w = framesInfo.getFrameW()+(framesInfo.getFrameMax()*framesInfo.getFrameOffsetX());
	imgInfo->h = framesInfo.getFrameH()+(framesInfo.getFrameMax()*framesInfo.getFrameOffsetY());
	SDL_Surface* spriteActionSheet = loadPartialSprieSheetAsSurface(path, imgInfo);

	if (spritesheets.count(spritename) != 0){ //if the sprite already exists
		std::map<std::string, SDL_Surface>* actionMap = &spritesheets.at(spritename); //I want to modify the data...
		if (actionMap->count(spriteaction) != 0){ //if the action already exists
			//do nothing
		} else {
			//create the sprite action
			actionMap->insert(std::pair<std::string,SDL_Surface>(spriteaction, *spriteActionSheet));
		}
	} else {
		//create both
		std::map<std::string, SDL_Surface>* actionMap = new std::map<std::string,SDL_Surface>();
		actionMap->insert(std::pair<std::string, SDL_Surface>(spriteaction, *spriteActionSheet)); //insert the new (first of many) spriteaction
		spritesheets.insert(std::pair<std::string, std::map<std::string, SDL_Surface> >(spritename, *actionMap));//insert this new data to the parent map
	}

	printf("Total %d spritesheets\n",spritesheets.size());

	delete spriteActionSheet;
	delete imgInfo;
}

SDL_Surface* ImageFactory::getImage(std::string n, std::string a){
	return &spritesheets.at(n).at(a);
}

SDL_Surface* ImageFactory::getSubImage(std::string n, std::string a, FrameManager* f){
	SDL_Surface* surface = getImage(n,a);
	SDL_Surface* frame = SDL_CreateRGBSurface(0,f->getFrameW(),f->getFrameH(),32,0,0,0,0);
	if (frame == NULL){
		printf("null\n");
	}
	SDL_Rect* src = new SDL_Rect();
	src->x = f->getFrameCur()*f->getFrameOffsetX();
	src->y = f->getFrameCur()*f->getFrameOffsetY();
	src->w = f->getFrameW();
	src->h = f->getFrameH();
	SDL_BlitSurface(surface,src,frame,NULL);
	delete src;
	delete surface;
	return frame;
}
