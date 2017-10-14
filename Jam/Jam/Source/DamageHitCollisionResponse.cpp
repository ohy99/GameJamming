#include "DamageHitCollisionResponse.h"

#include "Damage.h"
#include "Player.h"
#include "Enemy.h"
#include "DmgHitBox.h"
#include "CharacterBase.h"
#include "Faction.h"

DamageHitResponse::DamageHitResponse(Damage* damage_component) : damage_component(damage_component)
{
}
DamageHitResponse::DamageHitResponse() : damage_component(nullptr), faction_component(nullptr)
{
}

DamageHitResponse::~DamageHitResponse()
{
}

bool DamageHitResponse::response(GameObject * other, GameObject* my_owner)
{
	//list all class that will get affected by this
	//eg. Class* class = dynamic_cast<Class*>(other)
	//this will mean that Class has something to do with this
	CharacterBase* someguy = dynamic_cast<CharacterBase*>(other);

	if (someguy)
		if (someguy->faction.side != this->faction_component->side)
		{
			someguy->hitpoint.kena_hit(this->damage_component->get_dmg(), &other->pos);
			if (someguy->faction.side == Faction::FACTION_SIDE::ENEMY)
			{
				//if i hit tio enemy
				Player::GetInstance()->kill_feedback(someguy->hitpoint.get_hp_percentage() <= 0.f);
			}
			return true;
		}
	return false;
}
