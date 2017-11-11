#include "EnemyManager.h"

#include "Enemy.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include <fstream>
#include "MeshList.h"
#include "RenderHelper.h"
#include "Graphics.h"
#include "Loader.h"
#include "GlobalVariableManager.h"
#include "Player.h"
#include <iostream>
#include "MyDebugger.h"

EnemyManager::EnemyManager() : max_movespd(25.f), acceleration(10.f), initial_movespd(10.f),
spawn_wave(true), enemy_scale(7.5, 7.5f, 1), wave_number(0), max_wave(0)
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

void EnemyManager::init()
{
	deactivate_all();
	active_enemy.clear();

	current_pattern = -1;
	pattern_interval.set_duration(3.0);
	pattern_interval.reset_timer();
	spawn_interval.set_duration(0.0);
	spawn_interval.reset_timer();
	spawn_wave = true;
	wave_number = 0;
}

void EnemyManager::update(double dt)
{
	if (spawn_wave)
		check_spawn(dt);

	if (spawn_wave)
		MyDebugger::GetInstance()->watch_this_info("Wave Num", wave_number);

	//Updating active enemies
	//let enemies move along nodes
	for (std::list< std::pair<Enemy*, path_info > >::iterator iter = active_enemy.begin(); iter != active_enemy.end();)
	{
		std::pair<Enemy*, path_info >  &e = *iter;

		//update its own timer etc
		e.first->update(dt);
		e.first->inc_movespd(this->acceleration * (float)dt, this->max_movespd);

		if (e.first->hitpoint.get_hp_percentage() <= 0.f)
		{
			e.first->deactivate();
			Player::GetInstance()->add_point(100);
			iter = active_enemy.erase(iter);
			continue;
		}

		//check if i passed the end of the node
		if (e.second.current_node_iter != (*e.second.current_path).end())
		{
			//if my pos is at the current target node
			if (e.first->pos == (*e.second.current_node_iter))
			{
				//move the iterator one step forward
				e.second.current_node_iter = std::next(e.second.current_node_iter, 1);

				//if the iterator is at the end of the path
				if (e.second.current_node_iter == (*e.second.current_path).end())
				{
					//if im at the end node
					//let e keep going dir
					Vector3 nearest_end_pt = this->get_nearest_spawn(e.first->pos, e.first->dir);
					nearest_end_pt += e.first->scale.Length() * e.first->dir.Normalized();
					e.first->set_intended_pos(&nearest_end_pt);
				}
				else
				{
					//if the iterator is not at the end, i can safely get the pos and assign
					e.first->set_intended_pos(&(*e.second.current_node_iter));
				}
			}

		}
		else
		{
			//check if reach the ended intended pos
			if (e.first->pos == e.first->get_intended_pos())
			{
				e.first->deactivate();
				iter = active_enemy.erase(iter);
				continue;
			}
		}

		//++iter because there is no erase, can safely do it
		++iter;

	}

}

void EnemyManager::render()
{

}

void EnemyManager::set_max_wave(int num)
{
	this->max_wave = num;
}

//int EnemyManager::get_wave_number()
//{
//	return this->wave_number;
//}

bool EnemyManager::is_wave_ended()
{
	//if wave counter exceeds max and nothing is alive
	return this->wave_number > this->max_wave && !this->active_enemy.size();
}

void EnemyManager::reset_wave(bool active)
{
	this->spawn_wave = active;
	if (active)
		this->init();
}

void EnemyManager::check_spawn(double dt)
{
	spawn_interval.update_timer(dt);

	//random pattern
	rand_pattern(dt);

	if (current_pattern < 0)
		return;
	if (!spawn_interval.is_Duration_Passed())
		return;

	for (int path_index = 0; path_index < patterns.at(current_pattern).size(); ++path_index)
	{
		Enemy* e = this->get_inactive();
		if (!e)
			break;

		Vector3 spawn_pos;
		Vector3 spawn_dir;
		//step1: get the spawn point by using the first 2 points as guide.
		//meaning: spawn point, point1 and point 2 are one straight line.
		if (patterns.at(current_pattern).at(path_index).size() >= 2) {
			spawn_dir = -patterns.at(current_pattern).at(path_index).at(1) + patterns.at(current_pattern).at(path_index).at(0);
			spawn_pos = get_nearest_spawn(patterns.at(current_pattern).at(path_index).at(0), spawn_dir);
		}
		else
		{
			//only got 1 point
			spawn_pos = get_nearest_spawn(patterns.at(current_pattern).at(path_index).at(0), Vector3());
			spawn_dir = spawn_pos - patterns.at(current_pattern).at(path_index).at(0);
		}

		//hide the guy 
		spawn_pos += enemy_scale.Length() * spawn_dir.Normalized();
		e->set_intended_pos(&patterns.at(current_pattern).at(path_index).at(0));
		e->init(spawn_pos, enemy_scale, Vector3(0, 1, 0));

		path_info temp;
		temp.current_path = &patterns.at(current_pattern).at(path_index);
		temp.current_node_iter = temp.current_path->begin();
		//active_enemy.insert(std::make_pair(e, temp));
		active_enemy.push_back(std::make_pair(e, temp));
	}

	unsigned int num_of_path = patterns.at(current_pattern).size();
	float min_time = num_of_path * 1.0f;
	float max_time = num_of_path * 0.75f * 3.0f;
	spawn_interval.set_duration((double)Math::RandFloatMinMax(min_time, max_time));
	spawn_interval.reset_timer();
}

float EnemyManager::find_longest_distance(int pattern_index)
{
	float distance = 0.0f;
	for (int path_index = 0; path_index < patterns.at(pattern_index).size(); ++path_index)
	{
		std::vector<Vector3> &path = patterns.at(pattern_index).at(path_index);
		for (int node_index = 1; node_index < path.size(); ++node_index)
		{
			distance += (path.at(node_index) - path.at(node_index - 1)).Length();
		}
	}
	return distance;
}

void EnemyManager::rand_pattern(double dt)
{
	pattern_interval.update_timer(dt);
	if (!pattern_interval.is_Duration_Passed())
		return;

	spawn_interval.reset_timer();

	//rand dist
	if (patterns.size() > 1)
	{
		int prev_pattern = current_pattern;
		while (current_pattern == prev_pattern)
		{
			current_pattern = Math::RandIntMinMax(0, patterns.size() - 1);
		}
	}
	else
		current_pattern = 0;

	float longest_distance = find_longest_distance(current_pattern);

	//using s = ut + 0.5 a t^2
	//find t

	std::vector<float> result = Math::Quadratic(0.5f * acceleration, initial_movespd, -longest_distance);
	if (result.size() == 0)
	{
		std::cerr << "Result size for pattern(" << current_pattern << ") distance == 0\n";
		throw 0;
	}
	float longest_time = (result.size() == 2 ? (result.at(0) >= result.at(1) ? result.at(0) : result.at(1)) : result.at(0));

	//pattern_interval.set_duration((double)longest_time);
	pattern_interval.set_duration(10.0);
	pattern_interval.reset_timer();

	++wave_number;
	if (wave_number > max_wave)
		reset_wave(false);
}

Vector3 EnemyManager::get_nearest_spawn(Vector3 origin, Vector3 dir)
{
	//possible to spawn on either 2 side of the 4 sides
	try {
		dir.Normalize();
	}
	catch (DivideByZero) {
		dir.Set(Math::RandFloat(), Math::RandFloat());
		dir.Normalize();
	}
	int quadrant = (dir.x >= 0 ? (dir.y >= 0 ? 0 : 3) : (dir.y >= 0 ? 1 : 2));

	Vector3 minpt(0, 0, 0);
	Vector3 maxpt(GlobalVariables::GetInstance()->get_worldWidth(), GlobalVariables::GetInstance()->get_worldHeight());
	switch (quadrant)
	{
	case 1:
	{
		//spawn top and left

		//check top
		//find lambda
		float* toplambda = nullptr;
		float* leftlambda = nullptr;
		if (dir.y != 0)
			toplambda = new float((maxpt.y - origin.y) / dir.y);
		if (dir.x != 0)
			leftlambda = new float((minpt.x - origin.x) / dir.x);

		//use the smaller value
		//tip: if top and left sama sama, top will come first coz of <=
		float * smaller_value = nullptr;
		if (toplambda == nullptr)
			smaller_value = leftlambda;
		else if (leftlambda == nullptr)
			smaller_value = toplambda;
		else
			smaller_value = (*toplambda <= *leftlambda ? toplambda : leftlambda);

		Vector3 point = origin + *smaller_value * dir;

		delete toplambda;
		delete leftlambda;

		return point;
	}
	case 2:
	{
		//spawn bottom and left
		float* bottomlambda = nullptr;
		float* leftlambda = nullptr;
		if (dir.y != 0)
			bottomlambda = new float((minpt.y - origin.y) / dir.y);
		if (dir.x != 0)
			leftlambda = new float((minpt.x - origin.x) / dir.x);


		float * smaller_value = nullptr;
		if (bottomlambda == nullptr)
			smaller_value = leftlambda;
		else if (leftlambda == nullptr)
			smaller_value = bottomlambda;
		else
			smaller_value = (*bottomlambda <= *leftlambda ? bottomlambda : leftlambda);

		Vector3 point = origin + *smaller_value * dir;

		delete bottomlambda;
		delete leftlambda;
		return point;
	}
	case 3:
	{
		//spawn bottom and right
		float* bottomlambda = nullptr;
		float* rightlambda = nullptr;
		if (dir.y != 0)
			bottomlambda = new float((minpt.y - origin.y) / dir.y);
		if (dir.x != 0)
			rightlambda = new float((maxpt.x - origin.x) / dir.x);


		float * smaller_value = nullptr;
		if (bottomlambda == nullptr)
			smaller_value = rightlambda;
		else if (rightlambda == nullptr)
			smaller_value = bottomlambda;
		else
			smaller_value = ((*bottomlambda) <= *rightlambda ? bottomlambda : rightlambda);

		Vector3 point = origin + *smaller_value * dir;

		delete bottomlambda;
		delete rightlambda;
		return point;
	}
	default:
		//spawn top and right
		float* toplambda = nullptr;
		float* rightlambda = nullptr;
		if (dir.y != 0)
			toplambda = new float((maxpt.y - origin.y) / dir.y);
		if (dir.x != 0)
			rightlambda = new float((maxpt.x - origin.x) / dir.x);

		//use the smaller value
		float * smaller_value = nullptr;
		if (toplambda == nullptr)
			smaller_value = rightlambda;
		else if (rightlambda == nullptr)
			smaller_value = toplambda;
		else
			smaller_value = (*toplambda <= *rightlambda ? toplambda : rightlambda);

		Vector3 point = origin + *smaller_value * dir;

		delete toplambda;
		delete rightlambda;
		return point;
	}
	return Vector3();
}

Enemy * EnemyManager::get_inactive()
{
	for each (auto &e in enemy_pool)
		if (!e->active)
			return e;
	return nullptr;
}

void EnemyManager::deactivate_all()
{
	for each (auto e in enemy_pool)
		e->deactivate();
}
