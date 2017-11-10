#ifndef PEWPEWGUN_H
#define PEWPEWGUN_H

#include "Weapon.h"
#include "MeshList.h"

class PewPew : public Weapon
{
public:
	PewPew(Faction::FACTION_SIDE side) { 
		this->set(8, 10, 1.f, DmgHitBoxManager::DMG_COLLIDER_TYPE::ENEMYPROJ1, 25, side);
		this->mesh = MeshList::GetInstance()->getMesh("BLUELINE");
	}
	virtual void discharge();
	~PewPew() {}
};

#endif // !PEWPEWGUN_H

