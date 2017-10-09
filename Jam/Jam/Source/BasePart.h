#ifndef BASE_PART_H
#define BASE_PART_H

#include "Collider.h"
#include "CharacterBase.h"
#include "GameObject.h"
#include "Weapon.h"
class Boss;
class BasePart : public CharacterBase, public GameObject {
	friend Boss;
public:
	Collider* hitbox;
	std::string name;
	Weapon* weapon;

	virtual void update(double dt);
	virtual void render();

	void Activate();
	void Deactivate();
private:
	
protected:
	BasePart();
	virtual ~BasePart();
};

#endif