#ifndef BASE_PART_H
#define BASE_PART_H

#include "Collider.h"
#include "CharacterBase.h"
#include "GameObject.h"

class BasePart : public CharacterBase, public GameObject{
public:
	Collider* hitbox;
	std::string name;

private:
	
};

#endif