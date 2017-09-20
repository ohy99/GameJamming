#include "CollisionManager.h"

#include "ColliderBase.h"
#include "MyDebugger.h"

CollisionManager::CollisionManager()
{

}
CollisionManager::~CollisionManager() {

}

void CollisionManager::update(double dt)
{
	for (std::set<ColliderBase*>::iterator first_iter = colliders.begin(); first_iter != colliders.end(); ++first_iter)
	{

		std::set<ColliderBase*>::iterator second_iter = first_iter;
		for (std::advance(second_iter, 1); second_iter != colliders.end(); ++second_iter)
		{
			//check collision
			//response is activated inside the function if true
			(*first_iter)->check_collision(*second_iter);

		}
	}

	MyDebugger::GetInstance()->watch_this_info("COLLISION SIZE", colliders.size());
}

void CollisionManager::add_collider(ColliderBase* collidable)
{
	this->colliders.insert(collidable);
}

void CollisionManager::remove_collider(ColliderBase * collidable)
{
	this->colliders.erase(collidable);
}

//void CollisionManager::add_ground(Collidable * ground)
//{
//	this->ground = ground;
//}
//
//Collidable * CollisionManager::get_ground()
//{
//	return ground;
//}
