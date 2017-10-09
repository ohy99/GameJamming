#include "BasePart.h"

#include "CollisionManager.h"
#include "RenderManager.h"

BasePart::BasePart() : hitbox(nullptr), weapon(nullptr)
{
}

BasePart::~BasePart()
{
	delete hitbox;
	delete weapon;
}

void BasePart::update(double dt)
{
	weapon->update(dt);
	weapon->pos = this->pos;
}

void BasePart::render()
{
	GameObject::render();

	hitpoint.render_hpbar(Vector3(pos.x, pos.y + scale.y, pos.z), Vector3(scale.x, 1));
}

void BasePart::Activate()
{
	//heal to max hp
	hitpoint.kena_heal_maxhp(1.0f);

	CollisionManager::GetInstance()->add_collider(this->hitbox);
	RenderManager::GetInstance()->attach_renderable(this, 0);
	this->active = true;

	RenderManager::GetInstance()->attach_renderable(this->weapon, 1);
	this->weapon->active = true;
}

void BasePart::Deactivate()
{
	CollisionManager::GetInstance()->remove_collider(this->hitbox);
	RenderManager::GetInstance()->remove_renderable(this);
	this->active = false;

	RenderManager::GetInstance()->remove_renderable(this->weapon);
	this->weapon->active = false;
}
