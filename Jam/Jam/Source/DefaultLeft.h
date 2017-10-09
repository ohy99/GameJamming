#ifndef DEFAULTLEFT_H
#define DEFAULTLEFT_H

#include "BasePart.h"
#include "EnemyCollisionResponse.h"
#include "MeshList.h"
#include "BossDefaultGun.h"

class DefaultLeft : public BasePart
{
public:
	DefaultLeft() {
		//init da shietz here
		hitbox = new Collider(this, new EnemyResponse);
		hitbox->set_response(new EnemyResponse);

		hitpoint.init_hp(1000);
		faction.side = Faction::FACTION_SIDE::ENEMY;

		this->mesh = MeshList::GetInstance()->getMesh("RedQuad");

		weapon = new BossDefaultGun(this->faction.side);
	}
	~DefaultLeft() {}
};

#endif // !DEFAULTLEFT_H

