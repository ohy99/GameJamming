#ifndef ENEMY_H
#define ENEMY_H

#include "CharacterBase.h"
#include "GameObject.h"
#include "Faction.h"
class Collider;
class Weapon;

class Enemy : public CharacterBase, public GameObject
{
	Collider* collider;
	Weapon* weapon[2];
	//Variables
	float move_speed;
	Vector3* intended_pos;

	//Methods
	void update_movement(double dt);
	void update_weapon(double dt);

public:
	void init(Vector3 pos, Vector3 scale, Vector3 dir);
	void deactivate();
	//overwrite virtuals from gameobj
	void update(double dt);
	void render();

	void render_debug();
	Enemy();
	~Enemy();
protected:
};

#endif // !ENEMY_H

