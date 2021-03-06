#ifndef BAMBAMMELEE_H
#define BAMBAMMELEE_H

#include "Weapon.h"
#include "MeshList.h"

class BamBam : public Weapon
{
public:
	BamBam(Faction::FACTION_SIDE side) {
		this->set(80, 120, 1, DmgHitBoxManager::DMG_COLLIDER_TYPE::MELEE, 0, side);
		this->mesh = MeshList::GetInstance()->getMesh("REDLINE");
	}
	~BamBam() {}

	virtual void discharge();
	virtual void Handle(BaseMessage* msg);
};

#endif // !PEWPEWGUN_H

