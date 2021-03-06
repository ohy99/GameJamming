#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class GameObject;
#include "Vector3.h"
#include "Physics.h"

class PhysicsManager :public Singleton<PhysicsManager>
{
	friend Singleton;
	std::vector< std::pair<GameObject* , Physics* > > objects;

	//just a constant -vel.y value
	//const Vector3 gravity;
public:
	void update(double dt);
	void add_object(GameObject* go , Physics* physic);
	void remove_object(GameObject* go);
	//Vector3 get_gravity();
protected:
	PhysicsManager();
	virtual ~PhysicsManager();
};



#endif // !
