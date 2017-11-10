#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>
#include <set>
//class Collidable;
class Collider;
class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton;
	std::set<Collider*> colliders;

	std::vector<Collider*> newColliders;
public:
	void update(double dt);
	void add_collider(Collider* collidable);
	void addColliderAfter(Collider* collider);
	void remove_collider(Collider* collidable);
	//void add_ground(Collidable* ground);
	//Collidable* get_ground();
protected:
	CollisionManager();
	virtual ~CollisionManager();
};

#endif // !COLLISION_MANAGER_H