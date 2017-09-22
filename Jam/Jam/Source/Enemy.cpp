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

void Enemy::update_movement(double dt)
{
}

void Enemy::update_weapon(double dt)
{
	double et = 0.0;
	et += dt;
	if (et < 0.75)
		return;

	et = 0.0;

	Vector3 metoplayer = -this->pos + Player::GetInstance()->pos;
	weapon[0]->pos = this->pos;
	weapon[0]->dir = metoplayer;
	this->dir = metoplayer;

	weapon[0]->discharge();
}

void Enemy::init(Vector3 pos, Vector3 scale, Vector3 dir)
{
	this->pos = pos;
	this->scale = scale;
	this->dir = dir;
	this->active = true;

	this->mesh = MeshList::GetInstance()->getMesh("Quad");

	//RenderManager::GetInstance()->attach_renderable(this);

	//IMPORTANT. SET COLLISION
	collider->set_collision(Collision::CollisionType::AABB, &this->pos, -this->scale * 0.5f, this->scale * 0.5f);
	CollisionManager::GetInstance()->add_collider(this->collider);

	this->faction.side = Faction::ENEMY;
	//variables
	move_speed = 10.f;
	this->hitpoint.init_hp(100);
}
void Enemy::deactivate()
{
	this->active = false;
	CollisionManager::GetInstance()->remove_collider(this->collider);
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

void Enemy::render_debug()
{
}

Enemy::Enemy()
{
	this->collider = new Collider(this, new PlayerResponse);
	RenderManager::GetInstance()->attach_renderable(this);

	//WEAPON
	weapon[0] = new PewPew(this->faction.side);
	weapon[0]->scale.Set(1, 1);
	RenderManager::GetInstance()->attach_renderable(weapon[0], 1);
	weapon[0]->active = true;
	weapon[0]->name = "GUN";

	weapon[1] = new BamBam(this->faction.side);
	weapon[1]->scale.Set(1, 1);
	RenderManager::GetInstance()->attach_renderable(weapon[1], 1);
	weapon[1]->active = true;
	weapon[1]->name = "GUN";
}

Enemy::~Enemy()
{
	delete collider;
	for (int i = 0; i < sizeof(weapon)/sizeof(weapon[0]); ++i)
		delete weapon[i];
}
