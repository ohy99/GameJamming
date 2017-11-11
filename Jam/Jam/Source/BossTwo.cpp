#include "BossTwo.h"

#include "EnemyCollisionResponse.h"
#include "MeshList.h"
#include "BossDefaultGun.h"
#include "GlobalVariableManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "Player.h"
#include "Graphics.h"
#include "RenderHelper.h"

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
	this->scale.Set(15.f, 15.f, 0.f);
	this->hitbox->set_collision(Collision::CollisionType::AABB,
		&this->pos, -this->scale * 0.5f, this->scale * 0.5f);

	hitpoint.init_hp(2000);
	this->faction.side = Faction::FACTION_SIDE::ENEMY;

	this->dir.Set(-1, 0, 0);

	weapon = new BossDefaultGun(this->faction.side);

	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	this->pos.Set(worldWidth + 10, worldHeight * 0.5f, 0);
	intendedPos.Set(worldWidth - 10,
		worldHeight * 0.9f, 0);

	moveSpd = 10.f;

	CollisionManager::GetInstance()->add_collider(this->hitbox);
	RenderManager::GetInstance()->attach_renderable(this, 1);
	attack_timer.set_duration(0.4);

	Mesh* temp;
	temp = nullptr;
	switch (Math::RandIntMinMax(0, 2))
	{
	case 0:
		temp = MeshList::GetInstance()->getMesh("HarpyBoss2Attack");
		break;
	case 1:
		temp = MeshList::GetInstance()->getMesh("WolfAttack");
		break;
	case 2:
		temp = MeshList::GetInstance()->getMesh("HarpyBossAttack");
		break;
	}
	this->mesh = temp;

	//meshpair[0].first = MeshList::GetInstance()->getMesh("HarpyBossIdle");
	//meshpair[0].second.Set(0, 1, 1, 0.5f, true);
	//meshpair[1].first = MeshList::GetInstance()->getMesh("HarpyBossAttack");
	//currState = ENTER;
}

void BossTwo::Update(double dt)
{
	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	Vector3 pt1(worldWidth - 20, worldHeight * 0.9f);
	Vector3 pt2(worldWidth - 20, worldHeight * 0.1f);
	this->weapon->pos = this->pos;
	this->weapon->dir = (-this->pos + Player::GetInstance()->pos).Normalized();
	this->weapon->update(dt);
	attack_timer.update_timer(dt);

	if (attack_timer.get_current_percent() >= 1) {
		attack_timer.reset_timer();
		this->weapon->discharge();
	}

	Vector3 dirToIntended = -this->pos + intendedPos;
	if (dirToIntended.LengthSquared() >= (dirToIntended.Normalized() * moveSpd).LengthSquared())
	{
		//okay im not there yet so im gona move
		if (dirToIntended.LengthSquared() > moveSpd * moveSpd * (float)dt * (float)dt)
			this->pos += dirToIntended.Normalized() * moveSpd * (float)dt;
		else {
			this->pos += dirToIntended;
			currState = ATTACK;
		}
	}
	else {
		if (intendedPos == pt1)
			intendedPos = pt2;
		else
			intendedPos = pt1;
	}

	//if (currState == ENTER)
	//	meshpair[currState].second.Update(dt);
	//this->mesh = meshpair[currState].first;
	
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
