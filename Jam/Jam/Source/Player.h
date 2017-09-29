#ifndef PLAYER_H
#define PLAYER_H

#define DEBUGPLAYER 1

#include "SingletonTemplate.h"
#include "InputController.h"
#include "GameObject.h"
#include "Faction.h"
#include "CharacterBase.h"
class Weapon;
class Collider;
/********************************************************************************

NOTE:
	JK no note

********************************************************************************/
class Player : public Singleton<Player>, public CharacterBase, public GameObject
{
	friend Singleton<Player>;
	InputController& inputController;
	Collider* collider;
	Weapon* weapon[2];
	std::vector <Weapon*> weapon_list;
	unsigned curr_weap;
	//Variables
	float move_speed;

	//LOLL
	typedef unsigned int pt;
	pt point;
	float point_multiplier;

	//Methods
	void update_movement(double dt);
	void update_weapon(double dt);

public:
	void init();
	//overwrite virtuals from gameobj
	void update(double dt);
	void render();

	void render_debug();

	void add_point(pt point);
	pt get_point();
protected:
	Player();
	~Player();
};

#endif // !PLAYER_H

