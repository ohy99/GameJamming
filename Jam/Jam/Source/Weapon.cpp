#include "Weapon.h"

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "DmgHitBoxManager.h"
#include "DmgHitBox.h"
#include "DieToDistance.h"
#include "DieToTimer.h"
#include "RenderManager.h"

Weapon::Weapon() : proj_type(DmgHitBoxManager::PROJECTILE)
{
}

Weapon::~Weapon()
{
}

void Weapon::update(double dt)
{
	attackspeed_timer.update_timer(dt);
}

void Weapon::set(int min_dmg, int max_dmg, double attacks_per_sec, DmgHitBoxManager::DMG_COLLIDER_TYPE type, float force, Faction::FACTION_SIDE side)
{
	this->damage.set(min_dmg, max_dmg);
	this->attackspeed_timer.set_duration(1.0 / attacks_per_sec);
	this->proj_type = type;
	this->power.force = force;
	this->faction.side = side;
}
