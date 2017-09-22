#include "EnemyManager.h"

#include "Enemy.h"

void EnemyManager::update(double dt)
{
	for each (auto &e in enemy_pool)
		if (e->active)
		{
			e->update(dt);
			if (e->hitpoint.get_hp_percentage() <= 0)
				e->deactivate();
		}
}

Enemy * EnemyManager::get_inactive()
{
	for each (auto &e in enemy_pool)
		if (!e->active)
			return e;
	return nullptr;
}

EnemyManager::EnemyManager()
{
	for (int i = 0; i < 50; ++i)
	{
		enemy_pool.push_back(new Enemy);
	}
}

EnemyManager::~EnemyManager()
{
	for each (auto &e in enemy_pool)
		delete e;
	enemy_pool.clear();
}
