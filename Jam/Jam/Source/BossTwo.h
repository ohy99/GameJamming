#ifndef BOSSTWO_H
#define BOSSTWO_H

#include "BossBase.h"
#include "Collider.h"
#include "GameObject.h"
#include "HitPoints.h"
#include "Faction.h"
#include "Weapon.h"
#include "CharacterBase.h"

//One headed boi
class BossTwo : public BossBase, public GameObject, public CharacterBase
{
	Collider* hitbox;
	Weapon* weapon;
	Vector3 intendedPos;
	float moveSpd;

	enum STATE
	{
		ENTER,//Enter as in enter da screen
		ATTACK
	} currState;
public:
	BossTwo();
	~BossTwo();
	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();
	virtual bool IsDead();

	virtual void render();
};

#endif // !BOSSTWO_H

