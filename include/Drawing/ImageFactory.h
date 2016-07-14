#ifndef CLASSES_DRAWING_IMAGEFACTORY_H_
#define CLASSES_DRAWING_IMAGEFACTORY_H_

#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
#include "FrameManager.h"

class ImageFactory {
public:
	static ImageFactory* getInstance();

	SDL_Surface* loadSpriteSheetAsSurface(std::string);
	SDL_Surface* loadPartialSprieSheetAsSurface(std::string, SDL_Rect*);
	void addSpriteSheet(FrameManager, std::string, std::string, std::string);
	SDL_Surface* getSubImage(std::string, std::string, FrameManager*);

private:
	ImageFactory();

	//map stores for units. In each map is another map containing
	//-actions- for the units.
	//i.e. map->at(unitname)->at(action)
	//the frame is deduced via frame manager

	SDL_Surface* getImage(std::string, std::string);

	static std::map<std::string, std::map<std::string, SDL_Surface> > spritesheets;
	static ImageFactory* instance;



};

#endif
