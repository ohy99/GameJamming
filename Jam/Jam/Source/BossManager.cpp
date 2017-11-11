#include "BossManager.h"

#include "Boss.h"
#include "BossTwo.h"
#include "BossThree.h"

BossManager::BossManager()
{
	//currType = BOSSTYPE::BOSSTWO;
	bossArray[DEFAULT] = new Boss();
	bossArray[BOSSTWO] = new BossTwo();
	bossArray[BOSSTHREE] = new BossThree();
	int boss = Math::RandIntMinMax(0, (int)TYPE_COUNT - 1);
	currType = (BOSSTYPE)boss;
}

BossManager::~BossManager()
{
}

void BossManager::Init()
{
	int boss = Math::RandIntMinMax(0, TYPE_COUNT);
	currType = (BOSSTYPE)boss;
	bossArray[currType]->Init();
}

void BossManager::Update(double dt)
{
	bossArray[currType]->Update(dt);
}

void BossManager::Exit()
{
	bossArray[currType]->Exit();
}

bool BossManager::IsBossDead()
{
	return bossArray[currType]->IsDead();
}
