#include "BossTwo.h"

#include "EnemyCollisionResponse.h"
#include "MeshList.h"
#include "BossDefaultGun.h"
#include "GlobalVariableManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "Player.h"

BossTwo::BossTwo()
{
}

BossTwo::~BossTwo()
{
}

void BossTwo::Init()
{
	hitbox = new Collider(this, new EnemyResponse);
	hitbox->set_response(new EnemyResponse);
	this->scale.Set(10.f, 10.f, 0.f);
	this->hitbox->set_collision(Collision::CollisionType::AABB,
		&this->pos, -this->scale * 0.5f, this->scale * 0.5f);

	hitpoint.init_hp(1000);
	faction.side = Faction::FACTION_SIDE::ENEMY;

	this->mesh = MeshList::GetInstance()->getMesh("RedQuad");

	weapon = new BossDefaultGun(this->faction.side);

	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	this->pos.Set(worldWidth + 10, worldHeight * 0.5f, 0);
	intendedPos.Set(worldWidth - 10,
		worldHeight * 0.75f, 0);

	moveSpd = 10.f;

	CollisionManager::GetInstance()->add_collider(this->hitbox);
	RenderManager::GetInstance()->attach_renderable(this, 1);

}

void BossTwo::Update(double dt)
{
	this->weapon->pos = this->pos;
	this->weapon->dir = (-this->pos + Player::GetInstance()->pos).Normalized();
	this->weapon->update(dt);
	this->weapon->discharge();

	Vector3 dirToIntended = -this->pos + intendedPos;
	if (dirToIntended.LengthSquared() >= 0.f)
	{
		//okay im not there yet so im gona move
		if (dirToIntended.LengthSquared() > moveSpd * moveSpd * (float)dt * (float)dt)
			this->pos += dirToIntended.Normalized() * moveSpd * (float)dt;
		else
			this->pos += dirToIntended;
	}
}

void BossTwo::Exit()
{
	CollisionManager::GetInstance()->remove_collider(this->hitbox);
	RenderManager::GetInstance()->remove_renderable(this);
	this->active = false;

	RenderManager::GetInstance()->remove_renderable(this->weapon);
	this->weapon->active = false;
}

bool BossTwo::IsDead()
{
	return (this->hitpoint.get_hp_percentage() <= 0.f);
}

void BossTwo::render()
{
	GameObject::render();

	hitpoint.render_hpbar(Vector3(pos.x, pos.y + scale.y, pos.z), Vector3(scale.x, 1));
}
