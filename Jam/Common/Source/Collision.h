#ifndef _COLLISION_H
#define _COLLISION_H

#include "Vector3.h"
#include "MyMath.h"

struct Collision
{
	enum CollisionType
	{
		AABB,
		SPHERE,
		POINT,
	};

	CollisionType collisionType;
	Vector3 min, max;
	Vector3 *mid;
	float radius;
	Vector3 point;//from mid
	Vector3 normal;

	Collision(CollisionType type = CollisionType::AABB) : collisionType(type) {
		mid = nullptr;
	}

	~Collision() {
		mid = nullptr;
		point.Set(0, 0, 0);
	}

	void setCollisionType(CollisionType collisionType) {
		this->collisionType = collisionType;
	}

	bool isCollide(Collision& other) {
		if (this->collisionType == AABB && other.collisionType == AABB) {
			return this->isCollideAABB_AABB(other);
		}
		else if (this->collisionType == AABB && other.collisionType == SPHERE) {
			return this->isCollideAABB_SPHERE(other);
		}
		else if (this->collisionType == AABB && other.collisionType == POINT) {
			return other.isCollidePOINT_AABB(*this);
		}
		else if (this->collisionType == SPHERE && other.collisionType == AABB) {
			return other.isCollideAABB_SPHERE(*this);
		}
		else if (this->collisionType == SPHERE && other.collisionType == SPHERE) {
			return this->isCollideSPHERE_SPHERE(other);
		}
		else if (this->collisionType == SPHERE && other.collisionType == POINT) {
			return other.isCollidePOINT_SPHERE(*this);
		}
		else if (this->collisionType == POINT && other.collisionType == AABB) {
			return this->isCollidePOINT_AABB(other);
		}
		else if (this->collisionType == POINT && other.collisionType == SPHERE) {
			return this->isCollidePOINT_SPHERE(other);
		}
		else if (this->collisionType == POINT && other.collisionType == POINT) {
			//NO this is not possible unless...
			return (*this->mid + this->point) == (*other.mid + other.point);
		}
		return false;
	}

private:
	bool isCollideAABB_AABB(Collision& target) {
		return (this->mid->x + max.x >= target.mid->x + target.min.x &&
			this->mid->x + min.x <= target.mid->x + target.max.x &&
			this->mid->y + max.y >= target.mid->y + target.min.y &&
			this->mid->y + min.y <= target.mid->y + target.max.y &&
			this->mid->z + max.z >= target.mid->z + target.min.z &&
			this->mid->z + min.z <= target.mid->z + target.max.z
			);
	}
	bool isCollideAABB_SPHERE(Collision& Sphere) {
		float x = Math::Max(this->mid->x + this->min.x, Math::Min(Sphere.mid->x, this->mid->x + this->max.x));
		float y = Math::Max(this->mid->y + this->min.y, Math::Min(Sphere.mid->y, this->mid->y + this->max.y));
		float z = Math::Max(this->mid->z + this->min.z, Math::Min(Sphere.mid->z, this->mid->z + this->max.z));

		float distSq = (x - Sphere.mid->x) * (x - Sphere.mid->x) +
			(y - Sphere.mid->y) * (y - Sphere.mid->y) +
			(z - Sphere.mid->z) * (z - Sphere.mid->z);

		return distSq <= (Sphere.radius * Sphere.radius);
	}

	bool isCollidePOINT_AABB(Collision& AABB)
	{
		return (this->mid->x + this->point.x >= AABB.mid->x + AABB.min.x &&
			this->mid->x + point.x <= AABB.mid->x + AABB.max.x &&
			this->mid->y + point.y >= AABB.mid->y + AABB.min.y &&
			this->mid->y + point.y <= AABB.mid->y + AABB.max.y &&
			this->mid->z + point.z >= AABB.mid->z + AABB.min.z &&
			this->mid->z + point.z <= AABB.mid->z + AABB.max.z
			);
	}

	bool isCollidePOINT_SPHERE(Collision& Sphere) {
		float distSq = ((*this->mid + point).x - Sphere.mid->x) *  ((*this->mid + point).x - Sphere.mid->x) +
			((*this->mid + point).y - Sphere.mid->y) *  ((*this->mid + point).y - Sphere.mid->y) +
			((*this->mid + point).z - Sphere.mid->z) *  ((*this->mid + point).z - Sphere.mid->z);

		return distSq <= (Sphere.radius * Sphere.radius);
	}

	bool isCollideSPHERE_SPHERE(Collision& Sphere) {
		float distSq = (this->mid->x - Sphere.mid->x) * (this->mid->x - Sphere.mid->x) +
			(this->mid->y - Sphere.mid->y) * (this->mid->y - Sphere.mid->y) +
			(this->mid->z - Sphere.mid->z) * (this->mid->z - Sphere.mid->z);

		return distSq <= (this->radius + Sphere.radius) * (this->radius + Sphere.radius);
	}
};

#endif