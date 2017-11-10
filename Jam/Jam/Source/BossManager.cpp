#include "BossManager.h"

#include "Boss.h"
#include "BossTwo.h"

BossManager::BossManager()
{
	currType = BOSSTYPE::BOSSTWO;
	bossArray[DEFAULT] = new Boss();
	bossArray[BOSSTWO] = new BossTwo();
}

BossManager::~BossManager()
{
}

void BossManager::Init()
{
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
