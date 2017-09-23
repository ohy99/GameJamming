#include "EnemyManager.h"

#include "Enemy.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include <fstream>
#include "MeshList.h"
#include "RenderHelper.h"
#include "Graphics.h"

void EnemyManager::update(double dt)
{
	for each (auto &e in enemy_pool)
		if (e->active)
		{
			e->update(dt);
			if (e->hitpoint.get_hp_percentage() <= 0)
				e->deactivate();
		}


	//update_save(dt);
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

}

EnemyManager::~EnemyManager()
{
	for each (auto &e in enemy_pool)
		delete e;
	enemy_pool.clear();
}

void EnemyManager::load_patterns(char * file_path)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return;
	}

	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
		//if (strncmp("Cell Width,", buf, 11) == 0)
		{
			//sscanf_s((buf + 11), "%d", &charWidth);
		}
	
		//Vector3

		//patterns.push_back();
	}

}
