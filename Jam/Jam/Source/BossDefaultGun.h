#ifndef BOSSDEFAULTGUN_H
#define BOSSDEFAULTGUN_H

#include "Weapon.h"
#include "MeshList.h"

class BossDefaultGun : public Weapon
{
public:
	BossDefaultGun(Faction::FACTION_SIDE side) {
		this->set(8, 10, 1.f, DmgHitBoxManager::DMG_COLLIDER_TYPE::BOSS_PROJ, 20, side);
		this->mesh = MeshList::GetInstance()->getMesh("BLUELINE");
	}
	~BossDefaultGun() {}

	virtual void discharge();

};

#endif // !PEWPEWGUN_H

