#include "DmgHitBox.h"

#include "Collider.h"
#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "DieCondition.h"
#include "AOECollisionResponse.h"
#include "ProjectileCollisionResponse.h"
#include "RenderManager.h"
#include "ParticleManager.h"

DmgHitBox::DmgHitBox() : collider(nullptr), die_condition(nullptr)
{
}

DmgHitBox::DmgHitBox(const DmgHitBox & other) : collider(nullptr), die_condition(nullptr)
{
	this->collider = other.collider->duplicate(this);
	this->mesh = other.mesh;
	this->scale = other.scale;
}

DmgHitBox::~DmgHitBox()
{
	delete collider;
	if (die_condition)
		delete die_condition;
	
}

void DmgHitBox::set_inactive()
{
	this->active = false;
	if (die_condition)
	{
		delete die_condition;
		die_condition = nullptr;
	}
	CollisionManager::GetInstance()->remove_collider(this->collider);
	PhysicsManager::GetInstance()->remove_object(this);
	RenderManager::GetInstance()->remove_renderable(this);
	AOEResponse* aoeresponse = dynamic_cast<AOEResponse*>(this->collider->get_response());
	if (aoeresponse)
	{
		//need to reset collided vector
		aoeresponse->reset_response();
	}
	particleSpawn.reset_timer();
}

void DmgHitBox::update(double dt)
{
	if (die_condition)
	{
		die_condition->update(dt);
		if (die_condition->is_dead())
			this->set_inactive();
	}

	ProjectileResponse* pr = dynamic_cast<ProjectileResponse*>(this->collider->get_response());
	if (pr)
	{
		if (pr->get_isCollided())
			this->set_inactive();
	}

	if (this->faction.side == Faction::FACTION_SIDE::PLAYER)
	{
		particleSpawn.update_timer(dt);
		if (particleSpawn.is_Duration_Passed())
		{
			ParticleManager::GetInstance()->spawn_particle(ParticleManager::TYPE::BULLET_TRAIL, this->pos, this->dir);
			particleSpawn.reset_timer();
		}
	}
}

void DmgHitBox::set(Vector3 pos, Vector3 dir, Faction::FACTION_SIDE side, float velocity, int damage, DamageType::DMG_TYPE type)
{
	this->pos = pos;
	this->dir = dir;
	this->physic.velocity = dir * velocity;
	this->damage.set(damage, type);
	this->faction.side = side;
	particleSpawn.set_duration(0.1);
}
