#include "../../include/Event/KeyboardEvent.h"
KeyboardEvent::KeyboardEvent() {

}

bool KeyboardEvent::operator<(const KeyboardEvent& a) const{
	if(this->type != a.type){
		return true;
	} else if (this->keysym.sym != a.keysym.sym){
		return true;
	}
	return false;
}
