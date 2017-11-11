#include "Boss.h"

#include "CollisionManager.h"
#include "RenderManager.h"

#include "Player.h"
#include "GlobalVariableManager.h"
#include "Mtx44.h"

#include "DefaultLeft.h"
#include "DefaultMiddle.h"
#include "DefaultRight.h"

bool CheckDuplicate(BasePart* part, std::map<std::string, BasePart*> map){
	if (!map.empty()) {
		auto check = map.find(part->name);
		if (check != map.end())
			return true;
	}
	return false;
}

Boss::Boss() : leftPart(nullptr), middlePart(nullptr), rightPart(nullptr),
	middleScale(20, 20, 1), sideScale(15.f, 15.f, 1), moveSpd(10),
	bossDir(-1,0,0), bossRight(0,1,0)
{
	//create parts here
	Parts[LEFT].push_back(new DefaultLeft);
	Parts[MIDDLE].push_back(new DefaultMiddle);
	Parts[RIGHT].push_back(new DefaultRight);

	for (std::vector<BasePart*>::iterator it = Parts[LEFT].begin(); it != Parts[LEFT].end(); ++it)
	{
		(*it)->scale = sideScale;
		(*it)->hitbox->set_collision(Collision::CollisionType::AABB, &(*it)->pos, -(*it)->scale * 0.5f, (*it)->scale * 0.5f);
	}
	for (std::vector<BasePart*>::iterator it = Parts[MIDDLE].begin(); it != Parts[MIDDLE].end(); ++it)
	{
		(*it)->scale = middleScale;
		(*it)->hitbox->set_collision(Collision::CollisionType::AABB, &(*it)->pos, -(*it)->scale * 0.5f, (*it)->scale * 0.5f);
	}
	for (std::vector<BasePart*>::iterator it = Parts[RIGHT].begin(); it != Parts[RIGHT].end(); ++it)
	{
		(*it)->scale = sideScale;
		(*it)->hitbox->set_collision(Collision::CollisionType::AABB, &(*it)->pos, -(*it)->scale * 0.5f, (*it)->scale * 0.5f);
	}


	//fdk me 
	//getWorldWidth = &((*GlobalVariables::GetInstance()).get_worldWidth);
	//getWorldHeight = &((*GlobalVariables::GetInstance()).get_worldHeight);
}

Boss::~Boss()
{
	Deactivate();
}

void Boss::Init()
{
	//randoming part
	leftPart = this->GetRandomPart(SIDE::LEFT);
	middlePart = this->GetRandomPart(SIDE::MIDDLE);
	rightPart = this->GetRandomPart(SIDE::RIGHT);
	
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
	leftPart->mesh = temp;
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
	middlePart->mesh = temp;
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
	rightPart->mesh = temp;

	leftPart->dir.Set(-1, 0, 0);
	middlePart->dir.Set(-1, 0, 0);
	rightPart->dir.Set(-1, 0, 0);

	//put them inside managers
	ActivatePart(leftPart);
	ActivatePart(middlePart);
	ActivatePart(rightPart);

	//xiaoo logic
	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	currState = STATE::ENTER;
	middlePart->pos.Set(worldWidth + 10, worldHeight * 0.5f, 0);
	intendedPos.Set(worldWidth - 10,
		worldHeight * 0.5f, 0);

	attack_state = (ATTACK_STATE)1;
	attack_timer.set_duration(3.0);
}

BasePart * Boss::GetRandomPart(SIDE side)
{
	return Parts[side].at(Math::RandIntMinMax(0, Parts[side].size() - 1));
}

void Boss::Update(double dt)
{
	//update the internal components
	attack_timer.update_timer(dt);
	UpdatePart(leftPart, dt);
	UpdatePart(middlePart, dt);
	UpdatePart(rightPart, dt);
	if (attack_timer.is_Duration_Passed())
		attack_timer.reset_timer();

	Vector3 dirToIntended = -middlePart->pos + intendedPos;
	if (dirToIntended.LengthSquared() >= 0.f)
	{
		//okay im not there yet so im gona move
		if (dirToIntended.LengthSquared() > moveSpd * moveSpd * (float)dt * (float)dt)
			middlePart->pos += dirToIntended.Normalized() * moveSpd * (float)dt;
		else
			middlePart->pos += dirToIntended;
	}
	
	//put them in da right spot
	leftPart->pos = middlePart->pos + Vector3((middlePart->scale.x + leftPart->scale.x) * 0.5f * -bossRight.x,
		(middlePart->scale.y + leftPart->scale.y) * 0.5f -bossRight.y, 0);
	rightPart->pos = middlePart->pos + Vector3((middlePart->scale.x + rightPart->scale.x) * 0.5f * bossRight.x,
		(middlePart->scale.y + rightPart->scale.y) * 0.5f * -bossRight.y, 0);


	if (middlePart->pos == intendedPos && currState == STATE::ENTER)
	{
		currState = STATE::ATTACK;
	}

	//deactivating condition
	if (leftPart->hitpoint.get_hp_percentage() <= 0.f)
	{
		leftPart->active = false;
		CollisionManager::GetInstance()->remove_collider(leftPart->hitbox);
	}
	if (middlePart->hitpoint.get_hp_percentage() <= 0.f)
	{
		middlePart->active = false;
		CollisionManager::GetInstance()->remove_collider(middlePart->hitbox);
	}
	if (rightPart->hitpoint.get_hp_percentage() <= 0.f)
	{
		rightPart->active = false;
		CollisionManager::GetInstance()->remove_collider(rightPart->hitbox);
	}
}

void Boss::Exit()
{
	this->Deactivate();
}

bool Boss::RegisterPart(BasePart* part, SIDE side)
{
	switch (side) {
	case LEFT:
		if (!CheckDuplicate(part, leftParts)) {
			leftParts[part->name] = part;
			return true;
		}
		break;
	case MIDDLE:
		if (!CheckDuplicate(part, middleParts)) {
			middleParts[part->name] = part;
			return true;
		}
		break;
	case RIGHT:
		if (!CheckDuplicate(part, rightParts)) {
			rightParts[part->name] = part;
			return true;
		}
		break;
	}
	return false;
}

bool Boss::IsDead()
{
	if (!leftPart || !middlePart || !rightPart)
		return false;
	return !leftPart->active && !middlePart->active && !rightPart->active;
}

void Boss::Deactivate()
{
	DeactivatePart(leftPart);
	DeactivatePart(middlePart);
	DeactivatePart(rightPart);
}

void Boss::ActivatePart(BasePart * part)
{
	part->Activate();
}

void Boss::DeactivatePart(BasePart * part)
{
	part->Deactivate();
}

void Boss::UpdatePart(BasePart * part, double dt)
{
	if (!part->active)
		return;

	switch (attack_state)
	{
	case A1:
	{
		if (part == leftPart || part == rightPart)
		{
			part->update(dt);
			part->weapon->dir.Set(-1, 0, 0);
			float angle = 45.f * sin(attack_timer.get_current_percent() * Math::TWO_PI);
			Mtx44 rotation;
			rotation.SetToRotation(angle, 0, 0, 1);
			part->weapon->dir = rotation * part->weapon->dir;
			part->weapon->dir.Normalize();
			part->weapon->discharge();
		}
		else
		{
			part->update(dt);
			part->weapon->dir = (-part->pos + Player::GetInstance()->pos).Normalize();
			part->weapon->discharge();
		}

		break;
	}
	default:
		//this is the default aka attack_state == 0
		part->update(dt);
		part->weapon->dir = (-part->pos + Player::GetInstance()->pos).Normalize();
		if (attack_timer.get_current_percent() >= 1) {
			part->weapon->discharge();
			attack_timer.reset_timer();
		}
	}
}
