#include "Collider.h"

#include "GameObject.h"
#include "CollisionResponse.h"

Collider::Collider(GameObject * owner) : owner(owner), collision_response(nullptr)
{
}

Collider::Collider(GameObject * owner, CollisionResponse * collision_response) : owner(owner), collision_response(collision_response)
{
}

Collider::~Collider()
{
	delete collision_response;
}

void Collider::set_collision(Collision::CollisionType type, Vector3 * pos, Vector3 value1, Vector3 value2)
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

void Collider::set_collision(Collision::CollisionType type, Vector3 * pos, float value1)
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

void Collider::set_response(CollisionResponse * collision_response)
{
	if (this->collision_response)
	{
		delete this->collision_response;
		this->collision_response = nullptr;
	}
	this->collision_response = collision_response;
}

CollisionResponse * Collider::get_response()
{
	return collision_response;
}

bool Collider::check_collision(Collider * other)
{
	if (this->collision.isCollide(other->collision))
	{
		this->collision_response->response(other->get_owner(), this->get_owner());
		other->collision_response->response(this->get_owner(), other->get_owner());
		return true;
	}
	return false;
}

GameObject * Collider::get_owner()
{
	return owner;
}

Collider * Collider::duplicate(GameObject * owner)
{
	Collider* temp = new Collider(owner);
	temp->collision = this->collision;
	temp->collision.mid = &owner->pos;
	return temp;
	
}
