#ifndef DEFAULTLEFT_H
#define DEFAULTLEFT_H

#include "BasePart.h"
#include "EnemyCollisionResponse.h"
#include "MeshList.h"
#include "BossDefaultGun.h"
#include "Graphics.h"
#include "RenderHelper.h"

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

	virtual void render()
	{
		MS& ms = Graphics::GetInstance()->modelStack;

		ms.PushMatrix();
		ms.Translate(this->pos);
		ms.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)), 0, 0, 1);
		ms.Scale(this->scale);
		RenderHelper::RenderMesh(this->mesh, false);
		ms.PopMatrix();

		hitpoint.render_hpbar(Vector3(pos.x, pos.y + scale.y, pos.z), Vector3(scale.x, 1));
	

	}
};

#endif // !DEFAULTLEFT_H

