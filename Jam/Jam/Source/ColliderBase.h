#ifndef COLLIDERBASE_H
#define COLLIDERBASE_H

/**********************************************************

	Need this so can hold pointer to collider template

***********************************************************/
#include "Collision.h"
#include "Vector3.h"
class GameObject;
class ColliderBase abstract
{
public:
	virtual bool check_collision(ColliderBase* other) = 0;
	virtual void set(Collision::CollisionType type, Vector3 * pos, Vector3 value1, Vector3 value2 = 0) = 0;
	virtual void set(Collision::CollisionType type, Vector3 * pos, float value1) = 0;
	virtual ColliderBase* duplicate(GameObject* owner) = 0;
	virtual ~ColliderBase() {}
protected:
	ColliderBase() {}


};

#endif // !COLLIDERBASE_H

