#ifndef PEWPEWGUN_H
#define PEWPEWGUN_H

#include "Weapon.h"
#include "MeshList.h"

class PewPew : public Weapon
{
public:
	PewPew(Faction::FACTION_SIDE side) { 
		this->set(3, 7, 5, DmgHitBoxManager::DMG_COLLIDER_TYPE::PROJECTILE, 50, side);
		this->mesh = MeshList::GetInstance()->getMesh("BLUELINE");
	}
	~PewPew() {}
};

#endif // !PEWPEWGUN_H

