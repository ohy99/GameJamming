#ifndef DMGHITBOX_H
#define DMGHITBOX_H

#include "GameObject.h"

#include "Physics.h"
#include "Damage.h"
#include "Faction.h"
#include "MyTimer.h"
class Collider;
class DmgHitBoxManager;
class DieCondition;
class DmgHitBox : public GameObject
{
private:
	friend DmgHitBoxManager;

	Collider* collider;
	Physics physic;
	Damage damage;
	Faction faction;

	DieCondition* die_condition;
public:
	DmgHitBox();
	DmgHitBox(const DmgHitBox& other);
	virtual ~DmgHitBox();
	void set_inactive();
	void update(double dt);
	//call this function to initialize the values of hitbox
	void set(Vector3 pos, Vector3 dir, Faction::FACTION_SIDE side, float velocity, int damage, DamageType::DMG_TYPE type);
	void set_die_condition(DieCondition* die) { this->die_condition = die; }
	Physics* get_physics_component() { return &physic; }
	Collider* get_collider_component() { return collider; }
	Faction* get_faction_component() { return &faction; }
};

#endif // !DMGHITBOX_H
