#ifndef BOSSDEFAULTGUN_H
#define BOSSDEFAULTGUN_H

#include "Weapon.h"
#include "MeshList.h"

class BossDefaultGun : public Weapon
{
public:
	BossDefaultGun(Faction::FACTION_SIDE side) {
		this->set(8, 12, 100, DmgHitBoxManager::DMG_COLLIDER_TYPE::BOSS_PROJ, 30, side);
		this->mesh = MeshList::GetInstance()->getMesh("BLUELINE");
	}
	~BossDefaultGun() {}

	virtual void discharge();
	virtual void Handle(BaseMessage* msg);
};

#endif // !PEWPEWGUN_H

