#include "DamageHitCollisionResponse.h"

#include "Damage.h"
#include "Player.h"
#include "Enemy.h"
#include "DmgHitBox.h"
#include "CharacterBase.h"
#include "Faction.h"
#include "AudioPlayer.h"
#include "DmgHitBoxManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "PhysicsManager.h"
#include "MessageDispatcher.h"
#include "ConcreteMessage.h"

DamageHitResponse::DamageHitResponse(Damage* damage_component) : damage_component(damage_component)
{
}
DamageHitResponse::DamageHitResponse() : damage_component(nullptr), faction_component(nullptr)
{
}

DamageHitResponse::~DamageHitResponse()
{
}
#include "Collision.h"
#include "Collider.h"
#include "BossTwo.h"
bool DamageHitResponse::response(GameObject * other, GameObject* my_owner)
{
	//list all class that will get affected by this
	//eg. Class* class = dynamic_cast<Class*>(other)
	//this will mean that Class has something to do with this
	CharacterBase* someguy = dynamic_cast<CharacterBase*>(other);

	if (someguy)
	{
		//DmgHitBox* me = dynamic_cast<DmgHitBox*>(my_owner);
		//if (me) {
		//	if (me->get_collider_component()->getCollision().collisionType == Collision::LINE)
		//		int a = 0;
		//}
		//me = dynamic_cast<DmgHitBox*>(other);
		//if (me)
		//	if (me->get_collider_component()->getCollision().collisionType == Collision::LINE)
		//		int a = 0;
		//someguy->hitpoint.kena_hit(this->damage_component->get_dmg(), &other->pos);
		if (someguy->faction.side != this->faction_component->side)
		{
			someguy->hitpoint.kena_hit(this->damage_component->get_dmg(), &other->pos);
			if (someguy->faction.side == Faction::FACTION_SIDE::ENEMY)
			{
				//if i hit tio enemy
				Player::GetInstance()->kill_feedback(someguy->hitpoint.get_hp_percentage() <= 0.f);
				if (someguy->hitpoint.get_hp_percentage() <= 0.f)
				{
					if (Math::RandFloatMinMax(0.f, 1.f) <= 0.4f)
					{
						DmgHitBoxManager::DMG_COLLIDER_TYPE type = 
							(DmgHitBoxManager::DMG_COLLIDER_TYPE)Math::RandIntMinMax(DmgHitBoxManager::DMGBOOST,
								DmgHitBoxManager::HPBOOST);
						DmgHitBox* pup = DmgHitBoxManager::GetInstance()->get_hitbox(type);
						Vector3 randDir(Math::RandFloat(), Math::RandFloat());
						try {
							randDir.Normalize();
						}
						catch (DivideByZero) {
							randDir.Set(0, 1, 0);
						}
						pup->set(other->pos, randDir, Faction::FACTION_SIDE::PLAYER, 5.f, 0.f, DamageType::PROJECTILE);
						CollisionManager::GetInstance()->addColliderAfter(pup->get_collider_component());
						RenderManager::GetInstance()->attach_renderable(pup, 1);
						PhysicsManager::GetInstance()->add_object(pup, pup->get_physics_component());
						pup->active = true;
					}
				}
				AudioPlayer::GetInstance()->PlaySound2D("Hit", 0.2);
			}
			return true;
		}
		else
		{
			if (this->faction_component->side == Faction::FACTION_SIDE::PLAYER)
			{
				DmgHitBox* powerup = dynamic_cast<DmgHitBox*>(my_owner);
				switch (powerup->type)
				{
				case 1:
					MessageDispatcher::GetInstance()->Send("MachineGun",
						new MessageWeapon(MessageWeapon::MESSAGE_TYPE::APPLY_DAMAGE_BOOST));

					//must return true so can be removed later
					return true;
				case 2:
					MessageDispatcher::GetInstance()->Send("MachineGun",
						new MessageWeapon(MessageWeapon::MESSAGE_TYPE::APPLY_FIRERATE_BOOST));

					return true;
				case 3:
					MessageDispatcher::GetInstance()->Send("Player",
						new MessageWeapon(MessageWeapon::MESSAGE_TYPE::HEAL_UP));

					return true;
				}
				
			}
		
		}
	}
		
	return false;
}
