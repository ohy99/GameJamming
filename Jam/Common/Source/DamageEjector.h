#ifndef DAMAGEEJECTOR_H
#define DAMAGEEJECTOR_H

/************************************
	You know what i mean ;)
************************************/
#include "DamageType.h"
#include "MyMath.h"
class DamageEjector : public DamageType
{
	int min_dmg, max_dmg;
public:
	DamageEjector() : min_dmg(0), max_dmg(0) {}
	~DamageEjector() {}

	void set(int min_dmg, int max_dmg) { this->min_dmg = min_dmg; this->max_dmg = max_dmg; }
	void get_minmax(int & min_dmg, int & max_dmg) { min_dmg = this->min_dmg; max_dmg = this->max_dmg; }
	//Damage get_damage() { return Damage(Math::RandIntMinMax(min_dmg, max_dmg)); }
	int get_damage() { return Math::RandIntMinMax(min_dmg, max_dmg); }
};

#endif // !DAMAGEEJECTOR_H

/************************************

	Who knows? you might wan to add 
	element based attacks here too

************************************/