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

struct MessageCheckBuff : public BaseMessage {
	enum MESSAGE_TYPE {
		NONE = 0,
		CHECK_FIRERATE,
		CHECK_DAMAGE
	}type;

	MessageCheckBuff() {}
	MessageCheckBuff(MESSAGE_TYPE type, bool bol) : type(type), bol(bol) {}
	virtual ~MessageCheckBuff() {}

	bool bol;
};

#endif