#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <cstdio>
#include <string>

#include "../include/Drawing/DrawableWindow.h"
#include "../include/Drawing/FrameManager.h"
#include "../include/Drawing/ImageFactory.h"
#include "../include/Event/EventHandler.h"
#include "../include/Event/KeyboardEvent.h"
#include "../include/Unit/NPC.h"
#include "../include/Unit/Player.h"

//Testing setup

int timeDelta = SDL_GetTicks();
int nextFrame = timeDelta + 17;

//End

int main(int argc, char *argv[]){
	SDL_Init(SDL_INIT_EVERYTHING);

	DrawableWindow* window = DrawableWindow::getInstance(); //Get the instance of the client window (The context class)

	//Move below to the context class
	GameMap* map = new GameMap();
	//TESTING
	Unit* u = map->getUnitByName("player");
	Player* player = (Player*) u;
	//End test

	EventHandler<Player>* eventHandler = new EventHandler<Player>(player); //An event handler for player member functions

	//Events setup
	KeyboardEvent kE;
	kE.type = SDL_KEYDOWN;
	kE.keysym.sym = SDLK_DOWN;
	eventHandler->setKeyboardEvent(kE,&Player::moveDownEvent);
	kE.keysym.sym = SDLK_UP;
	eventHandler->setKeyboardEvent(kE,&Player::moveUpEvent);
	kE.keysym.sym = SDLK_LEFT;
	eventHandler->setKeyboardEvent(kE,&Player::moveLeftEvent);
	kE.keysym.sym = SDLK_RIGHT;
	eventHandler->setKeyboardEvent(kE,&Player::moveRightEvent);
	kE.type = SDL_KEYUP;
	kE.keysym.sym = SDLK_DOWN;
	eventHandler->setKeyboardEvent(kE,&Player::releaseDownEvent);
	kE.keysym.sym = SDLK_UP;
	eventHandler->setKeyboardEvent(kE,&Player::releaseUpEvent);
	kE.keysym.sym = SDLK_LEFT;
	eventHandler->setKeyboardEvent(kE,&Player::releaseLeftEvent);
	kE.keysym.sym = SDLK_RIGHT;
	eventHandler->setKeyboardEvent(kE,&Player::releaseRightEvent);
	//End
	printf("STARTING\n");
	int frame = 0;
	while(1){
		timeDelta = SDL_GetTicks();
		if (timeDelta > nextFrame){
			nextFrame = timeDelta + 17;
			eventHandler->pollEvents();

			//Just for testing

			player->move();
			if(frame % 9 == 0){
				player->animate();
				frame++;
			}

			//End

			window->renderMap(*map);
			window->drawScreen();
			frame++; // <-- For testing too

		}
	}

	SDL_Quit();
	return 0;
}



