#include "PhysicsManager.h"

#include "GameObject.h"


PhysicsManager::PhysicsManager() : gravity(0, -10, 0)
{

}
PhysicsManager::~PhysicsManager() {

}

void PhysicsManager::update(double dt) {

	for each (auto &go in objects)
	{
		if (go->active == false)
			continue;

		//go->update(dt);
		//Projectile* proj = dynamic_cast<Projectile*>(go);
		//if (proj)
		//{
		//	if (!proj->get_isCollidable())
		//		continue;
		//	if (proj->pos.y < 0)
		//		proj->active = false;

		//	proj->velocity += proj->get_mass() * gravity * (float)dt;
		//	proj->dir = proj->velocity.Normalized();
		//	proj->pos += proj->velocity * (float)dt;

		//}
	}
}

void PhysicsManager::add_object(GameObject* go)
{
	objects.push_back(go);
}

Vector3 PhysicsManager::get_gravity()
{
	return gravity;
}
