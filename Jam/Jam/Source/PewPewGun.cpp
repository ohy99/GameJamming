#include "PewPewGun.h"

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "DmgHitBoxManager.h"
#include "DmgHitBox.h"
#include "DieToDistance.h"
#include "DieToTimer.h"
#include "RenderManager.h"

void PewPew::discharge()
{
	//attackspd havent reach yet
	if (!attackspeed_timer.is_Duration_Passed())
		return;

	DmgHitBox* temp_proj = DmgHitBoxManager::GetInstance()->get_hitbox(proj_type);
	if (!temp_proj)
		return;
	temp_proj->set(this->pos, this->dir, this->faction.side, power.force, damage.get_damage(), damage.get_type());

	//i let u travel 50units bah
	temp_proj->set_die_condition(new DieToDistance(50, power.force));
	temp_proj->active = true;

	PhysicsManager::GetInstance()->add_object(temp_proj, temp_proj->get_physics_component());
	CollisionManager::GetInstance()->add_collider(temp_proj->get_collider_component());
	RenderManager::GetInstance()->attach_renderable(temp_proj, 1);

	AudioPlayer::GetInstance()->PlaySound2D("PewPew", 0.2);
	//must reset timer
	attackspeed_timer.reset_timer();
}