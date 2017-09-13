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

Player::Player() : inputController(*InputController::GetInstance()), collider(nullptr)
{
	//once only so yea
	collider = new Collider<PlayerResponse>(this);
}

Player::~Player()
{
}

void Player::init()
{
	this->pos.Set(GlobalVariables::GetInstance()->get_worldWidth() * 0.5f, GlobalVariables::GetInstance()->get_worldHeight() * 0.5f);
	this->scale.Set(3, 3, 3);
	this->dir.Set(0, 1, 0);
	this->active = true;

	this->mesh = MeshList::GetInstance()->getMesh("Cone");

	RenderManager::GetInstance()->attach_renderable(this);

	//IMPORTANT. SET COLLISION
	static_cast< Collider<PlayerResponse>* >(collider)->set(Collision::CollisionType::AABB, &this->pos, -this->scale, this->scale);
	CollisionManager::GetInstance()->add_collider(this->collider);

	//variables
	move_speed = 10.f;
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
		this->pos += this->dir * move_speed * (float)dt;
	}
	if (inputController.isInputDown(InputController::MOVE_BACK)) {
		this->pos += -this->dir * move_speed * (float)dt;
	}
	if (inputController.isInputDown(InputController::MOVE_LEFT)) {
		Vector3 right = this->dir.Cross(Vector3(0, 0, 1)).Normalize();
		this->pos += -right * move_speed * (float)dt;
	}
	if (inputController.isInputDown(InputController::MOVE_RIGHT)) {
		Vector3 right = this->dir.Cross(Vector3(0, 0, 1)).Normalize();
		this->pos += right * move_speed * (float)dt;
	}
}

void Player::update_weapon(double dt)
{
	if (inputController.isInputDown(InputController::SHOOT)) {

	}
	if (inputController.isInputDown(InputController::MELEE)) {

	}
}

void Player::render_debug()
{
	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
	ms.Translate(this->pos);

	//top line
	ms.PushMatrix();
	ms.Translate(0, this->scale.y, 0);
	ms.Scale(this->scale.x, 0, 0);
	RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("REDLINE"), false);
	ms.PopMatrix();

	//bot line
	ms.PushMatrix();
	ms.Translate(0, -this->scale.y, 0);
	ms.Scale(this->scale.x, 0, 0);
	RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("REDLINE"), false);
	ms.PopMatrix();

	//left line
	ms.PushMatrix();
	ms.Translate(-this->scale.x, 0, 0);
	ms.Rotate(90, 0, 0, 1);
	ms.Scale(this->scale.y, 0, 0);
	RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("GREENLINE"), false);
	ms.PopMatrix();

	//right line
	ms.PushMatrix();
	ms.Translate(this->scale.x, 0, 0);
	ms.Rotate(90, 0, 0, 1);
	ms.Scale(this->scale.y, 0, 0);
	RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("GREENLINE"), false);
	ms.PopMatrix();

	ms.PopMatrix();
}

//void Player::render()
//{
//}

