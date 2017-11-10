#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "Weapon.h"
#include "MeshList.h"

class MachineGun : public Weapon
{
public:
	MachineGun(Faction::FACTION_SIDE side) {
		this->set(8, 22, 10, DmgHitBoxManager::DMG_COLLIDER_TYPE::PROJECTILE, 100, side);
		this->mesh = MeshList::GetInstance()->getMesh("BLUELINE");
		chargeTime = 0;
	}
	~MachineGun() {}

	virtual void update(double dt);
	virtual void discharge();
private:
	float chargeTime;
};

#endif // !MACHINEGUN_H

