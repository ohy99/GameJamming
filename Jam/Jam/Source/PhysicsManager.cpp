#include "PhysicsManager.h"

#include "GameObject.h"


PhysicsManager::PhysicsManager() //: gravity(0, -10, 0)
{

}
PhysicsManager::~PhysicsManager() {

}

void PhysicsManager::update(double dt) {

	for each (auto &go in objects)
	{
		if (go.first->active == false)
			continue;

		//go->update(dt);
		//Projectile* proj = dynamic_cast<Projectile*>(go);
		//if (proj)
		//{
		//	if (!proj->get_isCollidable())
		//		continue;
		//	if (proj->pos.y < 0)
		//		proj->active = false;
		try {
			go.first->dir = go.second->velocity.Normalized();
		}
		catch (DivideByZero) {
			go.first->dir = go.first->dir;
		}
		go.first->pos += go.second->velocity * (float)dt;
		//	proj->velocity += proj->get_mass() * gravity * (float)dt;
		//	proj->dir = proj->velocity.Normalized();
		//	proj->pos += proj->velocity * (float)dt;

		//}
	}
}

void PhysicsManager::add_object(GameObject* go, Physics* physic)
{
	objects.push_back(std::make_pair (go, physic ));
}

void PhysicsManager::remove_object(GameObject * go)
{
	for (std::vector< std::pair<GameObject*, Physics* > > ::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		if (go == (*it).first)
		{
			it = objects.erase(it);
			return;
		}
	}
}

//Vector3 PhysicsManager::get_gravity()
//{
//	return gravity;
//}
