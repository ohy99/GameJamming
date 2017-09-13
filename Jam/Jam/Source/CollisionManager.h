#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>
#include <set>
//class Collidable;
class ColliderBase;
class CollisionManager : public Singleton<CollisionManager>
{
	friend Singleton;
	std::set<ColliderBase*> colliders;

public:
	void update(double dt);
	void add_collider(ColliderBase* collidable);
	void remove_collider(ColliderBase* collidable);
	//void add_ground(Collidable* ground);
	//Collidable* get_ground();
protected:
	CollisionManager();
	virtual ~CollisionManager();
};

#endif // !COLLISION_MANAGER_H