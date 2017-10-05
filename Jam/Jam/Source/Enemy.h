#ifndef ENEMY_H
#define ENEMY_H

#include "CharacterBase.h"
#include "GameObject.h"
#include "Faction.h"
#include "MyTimer.h"
class Collider;
class Weapon;

class Enemy : public CharacterBase, public GameObject
{
	Collider* collider;
	Weapon* weapon;
	//Variables
	float move_speed;
	Vector3* intended_pos;
	MyTimer slower_fire_rate;

	//Methods
	void update_movement(double dt);
	void update_weapon(double dt);

public:
	void init(Vector3 pos, Vector3 scale, Vector3 dir, float move_spd = 10.f, float hp = 100.f);
	void deactivate();
	//overwrite virtuals from gameobj
	void update(double dt);
	void render();
	void set_intended_pos(Vector3* pos);
	Vector3 get_intended_pos() { return Vector3(*intended_pos); }
	void inc_movespd(float increment, float max_value) { this->move_speed = Math::Min(this->move_speed + increment, max_value); }

	void render_debug();
	Enemy();
	~Enemy();
protected:
};

#endif // !ENEMY_H

