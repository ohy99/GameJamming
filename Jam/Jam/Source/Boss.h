#ifndef BOSS_H
#define BOSS_H

#include <map>
#include <set>

#include "BasePart.h"
#include "BossBase.h"

class Boss : public BossBase 
{
	enum ATTACK_STATE
	{
		DEFAULT_SHOOT_AT_ME,
		A1

	} attack_state;
	MyTimer attack_timer;
public:
	Boss();
	~Boss();

	enum SIDE {
		DEFAULT = 0,
		LEFT = 1,
		MIDDLE = 2,
		RIGHT = 3
	};

	virtual void Init();
	BasePart* GetRandomPart(SIDE side);
	virtual void Update(double dt);
	virtual void Exit();

	bool RegisterPart(BasePart* part, SIDE side);
	virtual bool IsDead();
	void Deactivate();
private:
	std::map<std::string, BasePart*> leftParts;
	std::map<std::string, BasePart*> middleParts;
	std::map<std::string, BasePart*> rightParts;
	std::vector<BasePart*> Parts[RIGHT + 1];

	BasePart* leftPart;
	BasePart* middlePart;
	BasePart* rightPart;

	//Activate their Colliders/Rendering
	void ActivatePart(BasePart* part);
	void DeactivatePart(BasePart* part);
	void UpdatePart(BasePart* part, double dt);

	//float(*getWorldWidth)();
	//float(*getWorldHeight)();

	enum STATE
	{
		ENTER,//Enter as in enter da screen
		ATTACK
	} currState;
	Vector3 intendedPos;
	Vector3 bossDir;
	Vector3 bossRight;
	Vector3 middleScale;
	Vector3 sideScale;
	float moveSpd;
};

#endif