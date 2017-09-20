#ifndef ENEMYINFO_H
#define ENEMYINFO_H

#include "CrowdControl.h"

class EnemyInfo : public CrowdControl
{
public:
	enum STATES
	{
		DEAD,
		MOVE,
		ATTACK,

		STATES_COUNT
	};
private:
	STATES currState;
public:
	bool change_state(STATES state);
protected:
	EnemyInfo();
	virtual ~EnemyInfo();

};

#endif // !ENEMYINFO_H

