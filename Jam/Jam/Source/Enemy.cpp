#include "Enemy.h"

#include "GlobalVariableManager.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "MouseController.h"
#include "Application.h"
#include "Collider.h"
#include "PlayerCollisionResponse.h"
#include "Graphics.h"
#include "RenderHelper.h"
#include "CollisionManager.h"
#include "Weapon.h"
#include "PewPewGun.h"
#include "BamBamMelee.h"
#include "MyDebugger.h"
#include "Player.h"
#include "EnemyCollisionResponse.h"

void Enemy::update_movement(double dt)
{
	if (!intended_pos)
		return;

	Vector3 metointended = -this->pos + *intended_pos;
	if (metointended.LengthSquared() == 0.f)
		return;

	if (metointended.LengthSquared() > move_speed * move_speed * (float)dt * (float)dt)
		this->pos += metointended.Normalized() * move_speed * (float)dt;
	else
		this->pos += metointended;

	this->dir = metointended.Normalized();

	weapon->pos = this->pos;
}

void Enemy::update_weapon(double dt)
{
	weapon->update(dt);


	slower_fire_rate.update_timer(dt);

	if (!slower_fire_rate.is_Duration_Passed())
		return;

	slower_fire_rate.reset_timer();

	Vector3 metoplayer = -this->pos + Player::GetInstance()->pos;
	weapon->pos = this->pos;
	weapon->dir = metoplayer.Normalized();
	//this->dir = metoplayer;

	weapon->discharge();
}

void Enemy::init(Vector3 pos, Vector3 scale, Vector3 dir, float move_spd, float hp)
{
	this->pos = pos;
	this->scale = scale;
	this->dir = dir;
	this->active = true;

	this->mesh = MeshList::GetInstance()->getMesh("EnemySide");

	RenderManager::GetInstance()->attach_renderable(this, 0);
	RenderManager::GetInstance()->attach_renderable(weapon, 1);

	//IMPORTANT. SET COLLISION
	collider->set_collision(Collision::CollisionType::AABB, &this->pos, -this->scale * 0.5f, this->scale * 0.5f);
	CollisionManager::GetInstance()->add_collider(this->collider);


	//variables
	move_speed = move_spd;
	this->hitpoint.init_hp(hp);

	slower_fire_rate.set_duration(0.75);

	weapon->active = true;
}
void Enemy::deactivate()
{
	this->active = false;
	CollisionManager::GetInstance()->remove_collider(this->collider);
	RenderManager::GetInstance()->remove_renderable(this);
	RenderManager::GetInstance()->remove_renderable(weapon);
	if (intended_pos)
	{
		delete intended_pos;
		intended_pos = nullptr;
	}
	weapon->active = false;
}

void Enemy::update(double dt)
{
	update_movement(dt);
	update_weapon(dt);
}

void Enemy::render()
{
	GameObject::render();

	hitpoint.render_hpbar(Vector3(pos.x, pos.y + scale.y, pos.z), Vector3(scale.x, 1));
}

void Enemy::set_intended_pos(Vector3 * pos)
{
	this->intended_pos = new Vector3(*pos);
}

void Enemy::render_debug()
{
}

Enemy::Enemy() : intended_pos(nullptr), move_speed(10.f)
{
	this->collider = new Collider(this, new EnemyResponse);
	//RenderManager::GetInstance()->attach_renderable(this);

	this->faction.side = Faction::ENEMY;
	//WEAPON
	weapon = new PewPew(this->faction.side);
	weapon->scale.Set(1, 1);
	weapon->active = true;
	weapon->name = "GUN";

}

Enemy::~Enemy()
{
	delete collider;
	delete weapon;

	if (intended_pos)
	{
		delete intended_pos;
		intended_pos = nullptr;
	}
}
