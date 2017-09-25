#include "EnemyCollisionResponse.h"

#include "Player.h"
#include "DmgHitBox.h"
#include "CameraManager.h"

EnemyResponse::EnemyResponse()
{
}

EnemyResponse::~EnemyResponse()
{
}

bool EnemyResponse::response(GameObject * other, GameObject * my_owner)
{
	DmgHitBox* player_damaging_hitbox = dynamic_cast<DmgHitBox*>(other);

	if (player_damaging_hitbox)
	{
		if (player_damaging_hitbox->get_faction_component()->side == Faction::PLAYER)
		{
			//shake shake shake
			CameraManager::GetInstance()->shake_cam(CameraManager::LIGHT);
		}
	}
	return false;
}
