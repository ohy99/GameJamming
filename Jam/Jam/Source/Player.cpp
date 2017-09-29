#include "Player.h"

#include "GlobalVariableManager.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "MouseController.h"
#include "Application.h"
#include "Collider.h"
#include "PlayerCollisionResponse.h"
#include "Graphics.h"
#include "RenderHelper.h"
#include "CollisionManager.h"
#include "Weapon.h"
#include "PewPewGun.h"
#include "BamBamMelee.h"
#include "MyDebugger.h"
#include "MachineGun.h"
#include "ShotGun.h"

Player::Player() : inputController(*InputController::GetInstance()), collider(nullptr)
{
	//once only so yea
	collider = new Collider(this, new PlayerResponse);
	this->faction.side = Faction::PLAYER;
}

Player::~Player()
{
	delete collider;
	for (int i = 0; i < sizeof(weapon) / sizeof(weapon[0]); ++i)
		delete weapon[i];

	for each (auto w in weapon_list)
	{
		delete w;
		w = nullptr;
	}
}

void Player::init()
{
	this->pos.Set(GlobalVariables::GetInstance()->get_worldWidth() * 0.5f, GlobalVariables::GetInstance()->get_worldHeight() * 0.5f);
	this->scale.Set(3, 3, 3);
	this->dir.Set(0, 1, 0);
	this->active = true;

	this->mesh = MeshList::GetInstance()->getMesh("Quad");

	RenderManager::GetInstance()->attach_renderable(this);

	//IMPORTANT. SET COLLISION
	collider->set_collision(Collision::CollisionType::AABB, &this->pos, -this->scale * 0.5f, this->scale * 0.5f);
	CollisionManager::GetInstance()->add_collider(this->collider);

	//WEAPON
	weapon[0] = new MachineGun(this->faction.side);
	weapon[0]->scale.Set(1, 1);
	
	RenderManager::GetInstance()->attach_renderable(weapon[0], 1);
	weapon[0]->active = true;
	weapon[0]->name = "GUN";

	weapon[1] = new BamBam(this->faction.side);
	weapon[1]->scale.Set(1, 1);
	RenderManager::GetInstance()->attach_renderable(weapon[1], 1);
	weapon[1]->active = true;
	weapon[1]->name = "GUN";

	Weapon* weap = new MachineGun(this->faction.side);
	weap->scale.Set(1, 1);
	weapon_list.push_back(weap);

	weap = new BamBam(this->faction.side);
	weap->scale.Set(1, 1);
	RenderManager::GetInstance()->attach_renderable(weap, 1);
	weap->active = true;
	weap->name = "GUN";
	weapon_list.push_back(weap);

	weap = new ShotGun(this->faction.side);
	weap->scale.Set(1, 1);
	RenderManager::GetInstance()->attach_renderable(weap, 1);
	weap->active = true;
	weap->name = "GUN";
	weapon_list.push_back(weap);

	curr_weap = 0;

	//variables
	move_speed = 30.f;
	this->hitpoint.init_hp(100);
	this->point_multiplier = 1.f;
	this->point = 0;
}

void Player::update(double dt)
{
	update_movement(dt);
	update_weapon(dt);

}

void Player::update_movement(double dt)
{
	double x, y;
	MouseController::GetInstance()->GetMousePosition(x, y);
	float w = Application::GetWindowWidth();
	float h = Application::GetWindowHeight();
	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

	try {
		this->dir = (-this->pos + cursor_point_in_world_space).Normalize();
	}
	catch (DivideByZero) {
		this->dir.Set(0, 1, 0);
	}
	
	if (inputController.isInputDown(InputController::MOVE_FRONT)) {
		//this->pos += this->dir * move_speed * (float)dt;
		this->pos += Vector3(0,1,0) * move_speed * (float)dt;
	}
	if (inputController.isInputDown(InputController::MOVE_BACK)) {
		//this->pos += -this->dir * move_speed * (float)dt;
		this->pos += -Vector3(0, 1, 0) * move_speed * (float)dt;
	}
	if (inputController.isInputDown(InputController::MOVE_LEFT)) {
		//Vector3 right = this->dir.Cross(Vector3(0, 0, 1)).Normalize();
		//this->pos += -right * move_speed * (float)dt;
		this->pos += -Vector3(1, 0, 0) * move_speed * (float)dt;
	}
	if (inputController.isInputDown(InputController::MOVE_RIGHT)) {
		//Vector3 right = this->dir.Cross(Vector3(0, 0, 1)).Normalize();
		//this->pos += right * move_speed * (float)dt;
		this->pos += Vector3(1, 0, 0) * move_speed * (float)dt;
	}
}

#include "KeyboardController.h"
void Player::update_weapon(double dt)
{
	weapon[0]->update(dt);
	weapon[0]->pos = this->pos;
	weapon[0]->dir = this->dir;
	weapon[1]->update(dt);
	weapon[1]->pos = this->pos;
	weapon[1]->dir = this->dir;
	for each(auto &w in weapon_list)
	{
		w->update(dt);
		w->pos = this->pos;
		w->dir = this->dir;
	}

	
	//if (inputController.isInputDown(InputController::SHOOT)) {
	//	weapon[0]->discharge();
	//}


	if (inputController.isInputDown(InputController::MELEE)) {
		weapon[1]->discharge();
	}

	//JUST DEBUG
	if (KeyboardController::GetInstance()->IsKeyPressed('Q'))
		curr_weap = Math::Wrap(curr_weap - 1, (unsigned)0, weapon_list.size() - 1);
	if (KeyboardController::GetInstance()->IsKeyPressed('E'))
		curr_weap = Math::Wrap(curr_weap + 1, (unsigned)0, weapon_list.size() - 1);

	if (inputController.isInputDown(InputController::SHOOT)) {
		weapon_list.at(curr_weap)->discharge();
	}
}

void Player::render_debug()
{
	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
	ms.Translate(this->pos);

	ms.PopMatrix();
}

void Player::add_point(pt point)
{
	this->point += (pt)(point * point_multiplier);
}

Player::pt Player::get_point()
{
	return this->point;
}

void Player::render()
{
	GameObject::render();

	hitpoint.render_hpbar(Vector3(pos.x, pos.y + scale.y, pos.z), Vector3(scale.x, 1));
}

