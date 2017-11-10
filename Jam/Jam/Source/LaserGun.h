#ifndef LASERGUN_H
#define LASERGUN_H

#include "Weapon.h"
#include "MeshList.h"

class LaserGun : public Weapon
{
public:
	LaserGun(Faction::FACTION_SIDE side) {
		this->set(33, 66, 3, DmgHitBoxManager::DMG_COLLIDER_TYPE::LASER, 50, side);
		this->mesh = MeshList::GetInstance()->getMesh("BLUELINE");
	}
	virtual void discharge();
	virtual void Handle(BaseMessage* msg);
	~LaserGun() {}
};

#endif // !PEWPEWGUN_H

