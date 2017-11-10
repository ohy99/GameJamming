#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Weapon.h"
#include "MeshList.h"

class ShotGun : public Weapon
{
	unsigned int num_of_spread;
	float total_angle_of_spread;//in deg
public:
	ShotGun(Faction::FACTION_SIDE side) : num_of_spread(5), total_angle_of_spread(30.f) {
		this->set(8, 15, 2, DmgHitBoxManager::DMG_COLLIDER_TYPE::PROJECTILE, 70, side);
		this->mesh = MeshList::GetInstance()->getMesh("REDLINE");
	}
	~ShotGun() {}

	virtual void discharge();
	virtual void Handle(BaseMessage* msg);
};

#endif // !ShotGun

