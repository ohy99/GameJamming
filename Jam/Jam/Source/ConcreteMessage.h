#ifndef CONCRETE_MESSAGE_H
#define CONCRETE_MESSAGE_H

class MessageWeapon {
public:
	enum MESSAGE_TYPE{
		NONE = 0,
		APPLY_DAMAGE_BOOST,
		APPLY_FIRERATE_BOOST,
	}type;

	float modifier;

	MessageWeapon(MESSAGE_TYPE type, float modifier)
		: type(type), modifier(modifier)
	{

	}
	virtual ~MessageWeapon() {}
};

#endif