#ifndef DEFAULTRIGHT_H
#define DEFAULTRIGHT_H

#include "BasePart.h"
#include "BossDefaultGun.h"

class DefaultRight : public BasePart {
public:
	DefaultRight() {
		//init da shietz here
		hitbox = new Collider(this, new EnemyResponse);

		hitpoint.init_hp(1000);
		faction.side = Faction::FACTION_SIDE::ENEMY;

		this->mesh = MeshList::GetInstance()->getMesh("BlueQuad");

		weapon = new BossDefaultGun(this->faction.side);
	}
	~DefaultRight() {}
};

#endif // !DEFAULTRIGHT_H
