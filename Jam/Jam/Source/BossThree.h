#ifndef BOSS_THREE_H
#define BOSS_THREE_H

#include <map>
#include <set>

#include "BasePart.h"
#include "BossBase.h"

class BossThree : public BossBase
{
	enum ATTACK_STATE
	{
		DEFAULT_SHOOT_AT_ME,
		A1

	} attack_state;
	MyTimer attack_timer;
public:
	BossThree();
	~BossThree();

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

	bool CheckDuplicate(BasePart* part, std::map<std::string, BasePart*> map) {
		if (!map.empty()) {
			auto check = map.find(part->name);
			if (check != map.end())
				return true;
		}
		return false;
	}

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
	Vector3 BossThreeDir;
	Vector3 BossThreeRight;
	Vector3 middleScale;
	Vector3 sideScale;
	float moveSpd;
};

#endif