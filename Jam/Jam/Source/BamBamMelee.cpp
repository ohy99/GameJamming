#include "BamBamMelee.h"

#include "DmgHitBox.h"
#include "CollisionManager.h"
#include "DieToTimer.h"

void BamBam::discharge()
{
	//attackspd havent reach yet
	if (!attackspeed_timer.is_Duration_Passed())
		return;

	DmgHitBox* temp_melee = DmgHitBoxManager::GetInstance()->get_hitbox(proj_type);
	if (!temp_melee)
		return;
	temp_melee->set(this->pos, this->dir, this->faction.side, power.force, damage.get_damage(), damage.get_type());

	//i let u travel 50units bah
	temp_melee->set_die_condition(new DieToTimer(1.f));
	temp_melee->active = true;

	//PhysicsManager::GetInstance()->add_object(temp_melee, temp_melee->get_physics_component());
	CollisionManager::GetInstance()->add_collider(temp_melee->get_collider_component());
	//must reset timer
	attackspeed_timer.reset_timer();
}
