#ifndef CLASSES_DRAWING_DRAWABLEWINDOW_H_
#define CLASSES_DRAWING_DRAWABLEWINDOW_H_

#include <SDL2/SDL_video.h>
#include "../Drawing/ImageFactory.h"
#include "../GameMap/GameMap.h"
struct SDL_Renderer;

class DrawableWindow{
public:
	static DrawableWindow* getInstance();

	void drawScreen();
	void renderMap(GameMap);
private:
	DrawableWindow();
	void drawBitmap(SDL_Surface*,SDL_Rect*);
	static DrawableWindow* instance;
	ImageFactory* imgFact;
	SDL_Renderer* renderer;
	SDL_Window* window;
};

#endif
