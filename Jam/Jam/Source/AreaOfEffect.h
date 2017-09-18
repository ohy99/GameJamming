#ifndef AOE_H
#define AOE_H

#include "GameObject.h"

//#include "Physics.h"
#include "Damage.h"
#include "Faction.h"
#include <vector>
class ColliderBase;
//class PhysicsManager;
class AOEManager;
class AreaOfEffect : public GameObject
{
	friend AOEManager;//this will set the collider of the aoe
	ColliderBase* collider;
	Damage damage;
	Faction faction;
	std::vector<ColliderBase*> collided;//store pointers of collided objects

	//Physics physic; //unless u wan knockback i guess
public:
	AreaOfEffect();
	AreaOfEffect(const AreaOfEffect& other);
	virtual ~AreaOfEffect();

	//call this function to initialize the values of proj
	void set(Vector3 pos, Vector3 dir, Faction::FACTION_SIDE side, float velocity, int damage);
	//Physics* get_physics_component() { return &physic; }
	ColliderBase* get_collider_component() { return collider; }
};

#endif // !PROJECTILE_H

