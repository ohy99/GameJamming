#ifndef HITPOINTCOMPONENT_H
#define HITPOINTCOMPONENT_H

#include "Vector3.h"

class HitPoint
{
	int hitpoint;
	int max_hitpoint;
public:
	HitPoint();
	~HitPoint();

	//IMPORTANT. init_hp() initialize the maxhp and hp
	void init_hp(int max_hp);
	//IMPORTANT. set_maxhp() do not changes the hp value, only the maxhp value is changed
	void set_maxhp(int max_hp);
	int get_maxhp();

	float get_hp_percentage();
	int get_hp();

	int kena_hit(int damage);
	int kena_hit_currenthp(float percent_of_current_hp);
	int kena_hit_maxhp(float percent_of_max_hp);

	int kena_heal(int damage);
	int kena_heal_currenthp(float percent_of_current_hp);
	int kena_heal_maxhp(float percent_of_max_hp);

	void render_hpbar(Vector3 pos, Vector3 scale, std::string foreground_mesh = "", std::string background_mesh = "");
};

#endif // !HITPOINTCOMPONENT_H

