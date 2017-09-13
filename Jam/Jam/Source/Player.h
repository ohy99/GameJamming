#ifndef PLAYER_H
#define PLAYER_H

#define DEBUGPLAYER 1

#include "SingletonTemplate.h"
#include "InputController.h"
#include "GameObject.h"

class ColliderBase;
/********************************************************************************

NOTE:
	public singleton, private gameobject. dont let other access gameobject info

********************************************************************************/
class Player : public Singleton<Player>, GameObject
{
	friend Singleton<Player>;
	InputController& inputController;
	ColliderBase* collider;

	//Variables
	float move_speed;

	//Methods
	void update_movement(double dt);
	void update_weapon(double dt);

public:
	void init();
	//overwrite virtuals from gameobj
	void update(double dt);
	//void render();

	void render_debug();
protected:
	Player();
	~Player();
};

#endif // !PLAYER_H

