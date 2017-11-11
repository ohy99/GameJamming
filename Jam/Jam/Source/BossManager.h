#ifndef BOSSMANAGER_H
#define BOSSMANAGER_H

#include "SingletonTemplate.h"
class BossBase;
class BossManager : public Singleton<BossManager>
{
	enum BOSSTYPE
	{
		DEFAULT = 0,
		BOSSTWO,
		BOSSTHREE,
		TYPE_COUNT
	} currType;
	BossBase* bossArray[TYPE_COUNT];
	friend Singleton<BossManager>;
	BossManager();
	~BossManager();
public:
	void Init();
	void Update(double dt);
	void Exit();

	bool IsBossDead();

};

#endif // !BOSSMANAGER_H

