#include "Particle.h"

#include "DieToTimer.h"
#include "RenderManager.h"
#include "PhysicsManager.h"

Particle::Particle() : dieCondition(nullptr)
{

}
Particle::~Particle()
{
	if (dieCondition)
		delete dieCondition;
}

void Particle::init(Vector3 pos, Vector3 dir, Vector3 scale, float speed, double active_duration)
{
	this->deactivate();
	dieCondition = new DieToTimer(active_duration);
	this->pos = pos;
	this->dir = dir;
	this->scale = scale;
	this->active = true;

	physic.velocity = this->dir * speed;
	RenderManager::GetInstance()->attach_renderable(this, 2);
	PhysicsManager::GetInstance()->add_object(this, &physic);
}
void Particle::update(double dt)
{
	if (dieCondition)
	{
		dieCondition->update(dt);
		if (dieCondition->is_dead())
			this->deactivate();
	}
}
void Particle::deactivate()
{
	this->active = false;
	if (dieCondition)
	{
		delete dieCondition;
		this->dieCondition = nullptr;
	}
	RenderManager::GetInstance()->remove_renderable(this);
	PhysicsManager::GetInstance()->remove_object(this);
}