#ifndef INCLUDE_EVENT_KEYBOARDEVENT_H_
#define INCLUDE_EVENT_KEYBOARDEVENT_H_

#include <SDL2/SDL_events.h>

class KeyboardEvent: public SDL_KeyboardEvent {
public:
	KeyboardEvent();
	bool operator<(const KeyboardEvent&) const;
private:

};

#endif
