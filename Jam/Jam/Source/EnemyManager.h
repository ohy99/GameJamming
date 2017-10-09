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

	Vector3 enemy_scale;

	std::list< std::pair<Enemy*, path_info > > active_enemy;
	float max_movespd;
	float acceleration;
	float initial_movespd;
	float max_hp;

	std::vector< std::vector< std::vector<Vector3> > > patterns;

	MyTimer spawn_interval;
	MyTimer pattern_interval;

	void check_spawn(double dt);
	float find_longest_distance(int pattern_index);
	int current_pattern;
	void rand_pattern(double dt);
	Vector3 get_nearest_spawn(Vector3 origin, Vector3 dir);

	int wave_number;
	int max_wave;

	bool spawn_wave;
public:
	void init();
	void update(double dt);
	void render();

	void set_max_wave(int num);
	//int get_wave_number();
	bool is_wave_ended();
	void reset_wave(bool active);

	Enemy* get_inactive();
	void deactivate_all();
protected:
	EnemyManager();
	~EnemyManager();
};

#endif // !ENEMYMANAGER_H

