#ifndef DAMAGECOMPONENT_H
#define DAMAGECOMPONENT_H

#include "DamageType.h"
//****************************************
//
//	Holds the value of damage. aka carrier
//
//*****************************************
class Damage : public DamageType
{
private:
	int damage;
public:
	Damage() : damage(0) {}
	Damage(int dmg) : damage(dmg) {}
	~Damage() {}
	void set(int dmg, DMG_TYPE type = DMG_TYPE::ENVIRONMENT ) { this->damage = dmg; this->type = type; }
	int get_dmg() { return damage; }
};

#endif // !DAMAGECOMPONENT_H

/**********************************
	Who knows? you may want to implement another damage
	mechanic such that it reduce over time / distance

***************/