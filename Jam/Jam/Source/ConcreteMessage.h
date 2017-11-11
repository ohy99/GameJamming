#ifndef CONCRETE_MESSAGE_H
#define CONCRETE_MESSAGE_H

#include "BaseMessage.h"

class MessageWeapon : public BaseMessage {
public:
	enum MESSAGE_TYPE{
		NONE = 0,
		APPLY_DAMAGE_BOOST,
		APPLY_FIRERATE_BOOST,
		HEAL_UP,
	}type;

	MessageWeapon(MESSAGE_TYPE type)
		: type(type){
	}
	virtual ~MessageWeapon() {}
};

#endif