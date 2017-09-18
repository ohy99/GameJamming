#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "GameObject.h"

#include "Physics.h"
#include "Damage.h"
#include "Faction.h"
class ColliderBase;
class PhysicsManager;
class ProjectileManager;
class Projectile : public GameObject
{
	friend PhysicsManager;//this will access the velocity of the proj
	friend ProjectileManager;//this will set the collider of the proj
	ColliderBase* collider;
	Physics physic;
	Damage damage;
	Faction faction;
public:
	Projectile();
	Projectile(const Projectile& other);
	virtual ~Projectile();

	//call this function to initialize the values of proj
	void set(Vector3 pos, Vector3 dir, Faction::FACTION_SIDE side, float velocity, int damage);
	Physics* get_physics_component() { return &physic; }
	ColliderBase* get_collider_component() { return collider; }
};

#endif // !PROJECTILE_H

