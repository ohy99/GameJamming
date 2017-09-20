#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "SingletonTemplate.h"
#include <vector>

class Enemy;
class EnemyManager : public Singleton<EnemyManager>
{
	friend Singleton<EnemyManager>;
	std::vector<Enemy*> enemy_pool;
public:
	
	void update(double dt);
	Enemy* get_inactive();
protected:
	EnemyManager();
	~EnemyManager();
};

#endif // !ENEMYMANAGER_H

