#ifndef INCLUDE_EVENT_EVENTHANDLER_H_
#define INCLUDE_EVENT_EVENTHANDLER_H_

#include <stddef.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_stdinc.h>
#include <map>
#include <stdexcept>
#include <utility>

#include "../Unit/Player.h"
#include "KeyboardEvent.h"

template<class T>class EventHandler {
public:

	typedef typename std::map<KeyboardEvent,void(T::*)()>::iterator Iterator;

	EventHandler(T* hook){
		this->hook = hook;
		event = new SDL_Event();
	}

	void setKeyboardEvent(KeyboardEvent keycode, void (T::*event)()){
		if(!hasEvent(keycode.type, keycode.keysym.sym)){
			this->events.insert(std::pair<KeyboardEvent,void(T::*)()>(keycode,event));
		}
	}

	void removeEvent(const unsigned int type, const int keycode){
		Iterator it = getEvent(type, keycode);
		if(hasEvent(event->type, event->key.keysym.sym)){
			try{
				Iterator re = it;
				++it;
				this->events.erase(re);
				return;
			} catch (std::out_of_range& e) {
			}
		}
	}


	void pollEvents(){
		while(SDL_PollEvent(event)){
			if(hasEvent(event->type, event->key.keysym.sym) && (event->type != SDL_KEYDOWN || event->type != SDL_KEYUP)){
				Iterator eventIt = getEvent(event->type, event->key.keysym.sym);
				void (T::*func)() = eventIt->second;
				(hook->*func)();
			}
		}
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		Iterator eventIt = events.begin();
		for(;eventIt != events.end();++eventIt){
			if(eventIt->first.type == SDL_KEYDOWN || eventIt->first.type == SDL_KEYUP){
				if(state[SDL_GetScancodeFromKey(eventIt->first.keysym.sym)]){
					void (T::*func)() = eventIt->second;
					(hook->*func)();
				}
			}
		}
	}

private:

	std::map<KeyboardEvent,void(T::*)()> events;
	SDL_Event* event;
	T* hook;

	Iterator getEvent(const unsigned int type, const int keycode){
		for(Iterator it = this->events.begin(); it != this->events.end(); ++it){
			KeyboardEvent k = it->first;
			if(k.type == type && k.keysym.sym == keycode){
				return it;
			}
		}
		throw new std::out_of_range("ERROR : Attempt to retrieve a non-existing event binding!");
	}

	bool hasEvent(const unsigned int type, const int keycode){
		Iterator it = this->events.begin();
		for(; it != this->events.end(); ++it){
			KeyboardEvent k = it->first;
			if(k.type == type && k.keysym.sym == keycode){
				return true;
			}
		}
		return false;
	}

};
#endif
