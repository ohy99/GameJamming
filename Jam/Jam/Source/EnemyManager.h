#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "SingletonTemplate.h"
#include <vector>

#include "Vector3.h"
#include "Collision.h"
class Enemy;
class Mesh;
class EnemyManager : public Singleton<EnemyManager>
{
public:

private:
	friend Singleton<EnemyManager>;
	std::vector<Enemy*> enemy_pool;

	std::vector< std::vector<Vector3> > patterns;

	//void update_save(double dt);
	void load_patterns(char* file_path);


public:
	
	void update(double dt);
	void render();
	Enemy* get_inactive();
protected:
	EnemyManager();
	~EnemyManager();
};

#endif // !ENEMYMANAGER_H

