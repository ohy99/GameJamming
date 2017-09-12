#include "CollisionManager.h"


CollisionManager::CollisionManager()
{

}
CollisionManager::~CollisionManager() {

}

void CollisionManager::update(double dt)
{
	//for (std::vector<Collidable*>::iterator first_iter = colliders.begin(); first_iter != colliders.end(); ++first_iter)
	//{
	//	if ((*first_iter)->active == false || !(*first_iter)->get_isCollidable())
	//		continue;


	//	for (std::vector<Collidable*>::iterator second_iter = first_iter + 1; second_iter != colliders.end(); ++second_iter)
	//	{
	//		if ((*second_iter)->active == false || !(*second_iter)->get_isCollidable())
	//			continue;

	//		if ((*first_iter)->collider.isCollide((*second_iter)->collider))
	//		{
	//			(*first_iter)->collision_response(*second_iter);
	//			(*second_iter)->collision_response(*first_iter);
	//		}
	//	}
	//}
}

//void CollisionManager::add_collider(Collidable* collidable)
//{
//	this->colliders.push_back(collidable);
//}
//
//void CollisionManager::add_ground(Collidable * ground)
//{
//	this->ground = ground;
//}
//
//Collidable * CollisionManager::get_ground()
//{
//	return ground;
//}
