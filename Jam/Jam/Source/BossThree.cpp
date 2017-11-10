#include "BossThree.h"

#include "CollisionManager.h"
#include "RenderManager.h"

#include "Player.h"
#include "GlobalVariableManager.h"
#include "Mtx44.h"

#include "DefaultLeft.h"
#include "DefaultMiddle.h"
#include "DefaultRight.h"

BossThree::BossThree() : leftPart(nullptr), middlePart(nullptr), rightPart(nullptr),
middleScale(10, 10, 1), sideScale(7.5f, 7.5f, 1), moveSpd(10),
BossThreeDir(-1, 0, 0), BossThreeRight(0, 1, 0)
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

BossThree::~BossThree()
{
	Deactivate();
}

void BossThree::Init()
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

	attack_state = (ATTACK_STATE)1;
	attack_timer.set_duration(3.0);
}

BasePart * BossThree::GetRandomPart(SIDE side)
{
	return Parts[side].at(Math::RandIntMinMax(0, Parts[side].size() - 1));
}

void BossThree::Update(double dt)
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
	leftPart->pos = middlePart->pos + Vector3((middlePart->scale.x + leftPart->scale.x) * 0.5f * -BossThreeRight.x,
		(middlePart->scale.y + leftPart->scale.y) * 0.5f - BossThreeRight.y, 0);
	rightPart->pos = middlePart->pos + Vector3((middlePart->scale.x + rightPart->scale.x) * 0.5f * BossThreeRight.x,
		(middlePart->scale.y + rightPart->scale.y) * 0.5f * -BossThreeRight.y, 0);


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

void BossThree::Exit()
{
	this->Deactivate();
}

bool BossThree::RegisterPart(BasePart* part, SIDE side)
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

bool BossThree::IsDead()
{
	if (!leftPart || !middlePart || !rightPart)
		return false;
	return !leftPart->active && !middlePart->active && !rightPart->active;
}

void BossThree::Deactivate()
{
	DeactivatePart(leftPart);
	DeactivatePart(middlePart);
	DeactivatePart(rightPart);
}

void BossThree::ActivatePart(BasePart * part)
{
	part->Activate();
}

void BossThree::DeactivatePart(BasePart * part)
{
	part->Deactivate();
}

void BossThree::UpdatePart(BasePart * part, double dt)
{
	if (!part->active)
		return;

	switch (attack_state)
	{
	case A1:
	{
		if (part == leftPart)
		{
			static int countLeft = 0;
			part->update(dt);		
			if (attack_timer.get_current_percent() >= 0.2) {
				if (countLeft > 5) {
					//attack_timer.reset_timer();
					part->weapon->dir.Set(0, 1, 0);
					countLeft = 0;
				}
				float angle = 90/5;
				Mtx44 rotation;
				rotation.SetToRotation(angle, 0, 0, 1);
				part->weapon->dir = rotation * part->weapon->dir;
				part->weapon->dir.Normalize();
				part->weapon->discharge();
				++countLeft;
			}
		}
		else if (part == rightPart) {
			static int countRight = 0;
			part->update(dt);
			if (attack_timer.get_current_percent() >= 0.2) {
				if (countRight > 5) {
					attack_timer.reset_timer();
					part->weapon->dir.Set(-1, 1, 0);
					countRight = 0;
				}
				float angle = 90 / 5;
				Mtx44 rotation;
				rotation.SetToRotation(angle, 0, 0, 1);
				part->weapon->dir = rotation * part->weapon->dir;
				part->weapon->dir.Normalize();
				part->weapon->discharge();
				++countRight;
			}
		}
		else
		{
			part->update(dt);
			part->weapon->dir = (-part->pos + Player::GetInstance()->pos).Normalize();
			static float t = 0;
			t += dt;
			if (t >= 0.5) {
				part->weapon->discharge();
				t = 0;
			}
		}

		break;
	}
	default:
		//this is the default aka attack_state == 0
		part->update(dt);
		part->weapon->dir = (-part->pos + Player::GetInstance()->pos).Normalize();
		part->weapon->discharge();
	}
}
