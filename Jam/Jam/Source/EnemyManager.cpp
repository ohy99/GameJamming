#include "EnemyManager.h"

#include "Enemy.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include <fstream>
#include "MeshList.h"
#include "RenderHelper.h"
#include "Graphics.h"
#include "Loader.h"

void EnemyManager::update(double dt)
{
	spawn_interval.update_timer(dt);

	//random pattern
	static int rand = Math::RandIntMinMax(0, patterns.size() - 1);
	patterns.at(rand);
	if (spawn_interval.is_Duration_Passed())
	{
		for (int path_index = 0; path_index < patterns.at(rand).size(); ++path_index)
		{
			for each (auto &e in enemy_pool)
				if (e->active)
				{
					patterns.at(rand).at(path_index);
				}
		}
		spawn_interval.reset_timer();
	}

	for each (auto &e in enemy_pool)
		if (e->active)
		{
			e->update(dt);
			if (e->hitpoint.get_hp_percentage() <= 0)
				e->deactivate();
		}


}

void EnemyManager::render()
{

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

	Loader::GetInstance()->load_pattern(patterns);
	spawn_interval.set_duration(1.0);
}

EnemyManager::~EnemyManager()
{
	for each (auto &e in enemy_pool)
		delete e;
	enemy_pool.clear();
}
