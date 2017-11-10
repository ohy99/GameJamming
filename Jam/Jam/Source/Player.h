#ifndef PLAYER_H
#define PLAYER_H

#define DEBUGPLAYER 1

#include "SingletonTemplate.h"
#include "InputController.h"
#include "GameObject.h"
#include "Faction.h"
#include "CharacterBase.h"
#include "MyTimer.h"
#include "Physics.h"
#include <utility>
#include "SpriteAnimation.h"
class Weapon;
class Collider;
class HUD;
/********************************************************************************

NOTE:
	JK no note

********************************************************************************/
class Player : public Singleton<Player>, public CharacterBase, public GameObject
{
	friend Singleton<Player>;
	friend HUD;
	InputController& inputController;
	Collider* collider;
	Weapon* weapon[2];
	Physics physic;
	std::vector <Weapon*> weapon_list; 
	unsigned curr_weap;
	//Variables
	float default_move_speed;
	float move_speed;
	bool legitDead;

	//LOLL
	typedef unsigned int pt;
	pt point;
	float point_multiplier;
	MyTimer combo_timer;
	double combo_duration;

	//Methods
	void update_movement(double dt);
	void update_weapon(double dt);

	//second wind
	bool second_wind_available;
	bool second_wind_active;
	MyTimer second_wind_timer;
	void update_second_wind(double dt);
	void go_down();
	void revive();

	//for animation
	std::pair<Mesh*, Animation> reticle;
	enum MESHSTATE
	{
		IDLE,
		FIRE,
		MESHSTATECOUNT
	} currMeshState;
	std::pair<Mesh*, Animation> meshArray[MESHSTATECOUNT];
	void changeState(MESHSTATE state);
public:
	void init();
	//overwrite virtuals from gameobj
	void update(double dt);
	void render();

	void render_debug();

	void add_point(pt point);
	pt get_point();
	MyTimer get_combo_timer();
	void add_combo();
	float get_multiplier();

	void kill_feedback(bool killed);
protected:
	Player();
	~Player();
};

#endif // !PLAYER_H

