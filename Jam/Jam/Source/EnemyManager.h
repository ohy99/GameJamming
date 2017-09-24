#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <set>
#include <utility>
#include <list>

#include "Vector3.h"
#include "Collision.h"
#include "MyTimer.h"
class Enemy;
class Mesh;
class EnemyManager : public Singleton<EnemyManager>
{
public:

private:
	typedef std::vector<Vector3>::iterator node_iter;
	struct path_info
	{
		std::vector< Vector3>::iterator current_node_iter;
		std::vector< Vector3>* current_path;
	};
	friend Singleton<EnemyManager>;
	std::vector<Enemy*> enemy_pool;


	std::list< std::pair<Enemy*, path_info > > active_enemy;

	std::vector< std::vector< std::vector<Vector3> > > patterns;

	MyTimer spawn_interval;

	void check_spawn(double dt);
	Vector3 get_nearest_spawn(Vector3 origin, Vector3 dir);
public:
	
	void update(double dt);
	void render();
	Enemy* get_inactive();
protected:
	EnemyManager();
	~EnemyManager();
};

#endif // !ENEMYMANAGER_H

