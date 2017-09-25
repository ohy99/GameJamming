#include "PlayerCollisionResponse.h"

#include "DmgHitBox.h"
#include "CameraManager.h"

PlayerResponse::PlayerResponse()
{
}

PlayerResponse::~PlayerResponse()
{
}

bool PlayerResponse::response(GameObject * other, GameObject* my_owner)
{
	//dynamic cast to see who hit me
	//would usually work unless u try to cast to shishanth
	//because u cant see shishanth hitting u
	//jk :3

	DmgHitBox* enemy_damaging_hitbox = dynamic_cast<DmgHitBox*>(other);

	if (enemy_damaging_hitbox)
	{
		if (enemy_damaging_hitbox->get_faction_component()->side == Faction::ENEMY)
		{
			//shake shake shake
			CameraManager::GetInstance()->shake_cam(CameraManager::HEAVY);
		}
	}
	return false;
}
