#include "CollisionManager.h"

#include "ColliderBase.h"

CollisionManager::CollisionManager()
{

}
CollisionManager::~CollisionManager() {

}

void CollisionManager::update(double dt)
{
	for (std::set<ColliderBase*>::iterator first_iter = colliders.begin(); first_iter != colliders.end(); ++first_iter)
	{
		//if ((*first_iter)->active == false || !(*first_iter)->get_isCollidable())
		//	continue;

		std::set<ColliderBase*>::iterator second_iter = first_iter;
		for (std::advance(second_iter, 1); second_iter != colliders.end(); ++second_iter)
		{
			//if ((*second_iter)->active == false || !(*second_iter)->get_isCollidable())
			//	continue;

			//check collision
			//response is activated inside the function if true
			(*first_iter)->check_collision(*second_iter);

		}
	}
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
