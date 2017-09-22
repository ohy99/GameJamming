#include "Weapon.h"

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "DmgHitBoxManager.h"
#include "DmgHitBox.h"
#include "DieToDistance.h"
#include "DieToTimer.h"

Weapon::Weapon() : proj_type((DmgHitBoxManager::DMG_COLLIDER_TYPE)0)
{
}

Weapon::~Weapon()
{
}

void Weapon::update(double dt)
{
	attackspeed_timer.update_timer(dt);
}

void Weapon::discharge()
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
	//must reset timer
	attackspeed_timer.reset_timer();
}

void Weapon::set(int min_dmg, int max_dmg, double attacks_per_sec, DmgHitBoxManager::DMG_COLLIDER_TYPE type, float force, Faction::FACTION_SIDE side)
{
	this->damage.set(min_dmg, max_dmg);
	this->attackspeed_timer.set_duration(1.0 / attacks_per_sec);
	this->proj_type = type;
	this->power.force = force;
	this->faction.side = side;
}
