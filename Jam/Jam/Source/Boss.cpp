#include "Boss.h"

#include "CollisionManager.h"
#include "RenderManager.h"

#include "Player.h"
#include "GlobalVariableManager.h"

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
	middleScale(10, 10, 1), sideScale(7.5f, 7.5f, 1), moveSpd(10),
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

void Boss::init()
{
	//randoming part
	leftPart = this->GetRandomPart(SIDE::LEFT);
	middlePart = this->GetRandomPart(SIDE::MIDDLE);
	rightPart = this->GetRandomPart(SIDE::RIGHT);
	
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
}

BasePart * Boss::GetRandomPart(SIDE side)
{
	return Parts[side].at(Math::RandIntMinMax(0, Parts[side].size() - 1));
}

void Boss::update(double dt)
{
	//update the internal components
	UpdatePart(leftPart, dt);
	UpdatePart(middlePart, dt);
	UpdatePart(rightPart, dt);

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
		leftPart->active = false;
	if (middlePart->hitpoint.get_hp_percentage() <= 0.f)
		middlePart->active = false;
	if (rightPart->hitpoint.get_hp_percentage() <= 0.f)
		rightPart->active = false;
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

	part->update(dt);
	part->weapon->dir = (-part->pos + Player::GetInstance()->pos).Normalize();
	part->weapon->discharge();
}
