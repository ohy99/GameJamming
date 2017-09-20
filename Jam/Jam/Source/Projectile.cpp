#include "Projectile.h"

#include "ColliderBase.h"
#include "Collider.h"
#include "ProjectileCollisionResponse.h"
#include "DamageHitCollisionResponse.h"

Projectile::Projectile() : collider(nullptr)
{
}

Projectile::Projectile(const Projectile& other)
{
	//this->collider = new Collider<ProjectileResponse>(this);
	this->collider = other.collider->duplicate(this);
	this->mesh = other.mesh;
	this->scale = other.scale;

}

Projectile::~Projectile()
{
	delete collider;
}

void Projectile::set(Vector3 pos, Vector3 dir, Faction::FACTION_SIDE side, float velocity, int damage)
{
	this->pos = pos;
	this->dir = dir;
	this->physic.velocity = dir * velocity;
	this->damage.set(damage);
	this->faction.side = side;

	DamageHitResponse* dhr = dynamic_cast<DamageHitResponse *>(this->collider);
	dhr->attach_faction_component(&this->faction);
}
