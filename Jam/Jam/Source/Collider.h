#ifndef COLLIDER_H
#define COLLIDER_H

#include "Collision.h"
#include "ColliderBase.h"

class GameObject;
template<class Response>
class Collider : public Response, public ColliderBase
{
	Collision collision;
	GameObject* owner;
public:
	Collider(GameObject* owner) { this->owner = owner; }
	~Collider() {}
	//type : AABB / Sphere / Point-relative to pos
	//pos : reference of the object position
	//value1 : if AABB. min. if Sphere, radius. if Point-relative to pos, displacement
	//value2 : only and ONLY if AABB is type. it will be used for MAX
	void set(Collision::CollisionType type, Vector3 * pos, Vector3 value1, Vector3 value2 = 0);
	void set(Collision::CollisionType type, Vector3 * pos, float value1);

	bool check_collision(ColliderBase* other);
	GameObject* get_owner() { return owner; }
};


#endif

template<class Response>
inline void Collider<Response>::set(Collision::CollisionType type, Vector3 * pos, Vector3 value1, Vector3 value2)
{
	switch (type)
	{
	case Collision::CollisionType::AABB:
		collision.setCollisionType(Collision::CollisionType::AABB);
		collision.mid = pos;
		collision.min = value1;
		collision.max = value2;
		return;
	case Collision::CollisionType::POINT:
		collision.setCollisionType(Collision::CollisionType::POINT);
		collision.mid = pos;
		collision.point = value1;
		return;
	}

	std::cout << "ERROR SETTING COLLIDER ON " << this << "!" << std::endl;
	throw 0;
}

template<class Response>
inline void Collider<Response>::set(Collision::CollisionType type, Vector3 * pos, float value1)
{
	switch (type)
	{
	case Collision::CollisionType::SPHERE:
		collision.setCollisionType(Collision::CollisionType::SPHERE);
		collision.mid = pos;
		collision.radius = value1;
		return;
	}

	std::cout << "ERROR SETTING COLLIDER ON " << this << "!" << std::endl;
	throw 0;
}

template<class Response>
inline bool Collider<Response>::check_collision(ColliderBase * other)
{
	Collider* other_collider = static_cast<Collider*>(other);

	if (this->collision.isCollide(other_collider->collision))
	{
		this->Response::response(other_collider->get_owner());
		other_collider->Response::response(this->get_owner());
		return true;
	}
	return false;
}


//.
//.
//.
//.
//.
// Yes I know... I regret using template too ):