#include "AreaOfEffect.h"

#include "Collider.h"

AreaOfEffect::AreaOfEffect()
{
}

AreaOfEffect::AreaOfEffect(const AreaOfEffect & other)
{
	this->collider = other.collider->duplicate(this);
	this->mesh = other.mesh;
	this->scale = other.scale;
}

AreaOfEffect::~AreaOfEffect()
{
	delete collider;
	collided.clear();
}

void AreaOfEffect::set(Vector3 pos, Vector3 dir, Faction::FACTION_SIDE side, float velocity, int damage)
{
	this->pos = pos;
	this->dir = dir;
	//this->physic.velocity = dir * velocity;
	this->damage.set(damage);
	this->faction.side = side;
}
