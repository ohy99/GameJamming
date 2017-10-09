#ifndef DEFAULTMIDDLE_H
#define DEFAULTMIDDLE_H

#include "BasePart.h"
#include "BossDefaultGun.h"

class DefaultMiddle : public BasePart {
public:
	DefaultMiddle() {
		//init da shietz here
		hitbox = new Collider(this, new EnemyResponse);
		hitbox->set_response(new EnemyResponse);

		hitpoint.init_hp(1000);
		faction.side = Faction::FACTION_SIDE::ENEMY;

		this->mesh = MeshList::GetInstance()->getMesh("GreenQuad");

		weapon = new BossDefaultGun(this->faction.side);
	}
	~DefaultMiddle() {}
};

#endif // !DEFAULTMIDDLE_H
