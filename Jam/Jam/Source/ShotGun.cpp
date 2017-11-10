#include "ShotGun.h"

#include "DieToDistance.h"
#include "DmgHitBox.h"
#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "Mtx44.h"
#include "RenderManager.h"

void ShotGun::discharge()
{
	if (!attackspeed_timer.is_Duration_Passed())
		return;

	float half_angle = total_angle_of_spread * 0.5f;
	Vector3 start_dir = this->dir;
	Mtx44 rotation;
	rotation.SetToRotation(-half_angle, 0, 0, 1);
	start_dir = rotation * start_dir;
	start_dir.Normalize();

	for (unsigned i = 0; i < num_of_spread; ++i)
	{
		DmgHitBox* proj = DmgHitBoxManager::GetInstance()->get_hitbox(proj_type);
		if (!proj)
			return;
		float angle_btw = total_angle_of_spread / (num_of_spread - 1);
		Mtx44 one_rotate;
		one_rotate.SetToRotation(angle_btw, 0, 0, 1);
		start_dir = one_rotate * start_dir;
		start_dir.Normalize();

		proj->set(this->pos, start_dir, this->faction.side, power.force, damage.get_damage(), damage.get_type());

		//i let u travel 50units bah
		proj->set_die_condition(new DieToDistance(50.f, power.force));
		proj->active = true;

		PhysicsManager::GetInstance()->add_object(proj, proj->get_physics_component());
		CollisionManager::GetInstance()->add_collider(proj->get_collider_component());
		RenderManager::GetInstance()->attach_renderable(proj, 1);
		//must reset timers
	}
	AudioPlayer::GetInstance()->PlaySound2D("Shotgun", 0.2);

	attackspeed_timer.reset_timer();
}

void ShotGun::Handle(BaseMessage* msg)
{
}
