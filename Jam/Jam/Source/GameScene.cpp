//gamescene.cpp
#include "GameScene.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshList.h"
#include "RenderHelper.h"
#include "Graphics.h"

#include "GlobalVariableManager.h"
#include "MeshBuilder.h"
#include "SceneManager.h"

#include "CollisionManager.h"
#include "PhysicsManager.h"
#include "GameObjectManager.h"
#include "EnvironmentManager.h"
#include "RenderManager.h"
#include "ShowHpManager.h"
#include "SpriteAnimation.h"
#include "MyDebugger.h"
#include "FontTypeManager.h"
#include "KeyboardController.h"
#include "MouseController.h"
#include "Player.h"
//#include "ProjectileManager.h"
#include "DmgHitBoxManager.h"
#include "EnemyManager.h"
#include "Enemy.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
	GameObjectManager::Destroy();
	MeshList::Destroy();
	EnvironmentManager::Destroy();
	RenderManager::Destroy();
	ShowHpManager::Destroy();
	
	FontTypeManager::Destroy();
	//ProjectileManager::Destroy();
	Player::Destroy();

	DmgHitBoxManager::Destroy();
	ShowHpManager::Destroy();
	EnemyManager::Destroy();

	InputController::Destroy();
	MyDebugger::Destroy();
	MouseController::Destroy();
	KeyboardController::Destroy();
}

void GameScene::Init()
{

	glClearColor(0.0f, 0.0f, 0.f, 0.0f);
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	Graphics::GetInstance()->init();
	Math::InitRNG();

	MouseController::GetInstance()->SetKeepMouseCentered(false);

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));
	axis = MeshBuilder::GenerateAxes("", 100, 100, 100);

	worldHeight = 100;
	worldWidth = worldHeight * Application::GetWindowWidth() / Application::GetWindowHeight();

	GlobalVariables::GetInstance()->worldWidth = &this->worldWidth;
	GlobalVariables::GetInstance()->worldHeight = &this->worldHeight;
	//Player init must be called after this 2 lines. because world width and height is used (for now)
	InputController::GetInstance()->init();//insert file here
	Player::GetInstance()->init();

	//ProjectileManager::GetInstance();
	EnemyManager::GetInstance();
	DmgHitBoxManager::GetInstance();
	ShowHpManager::GetInstance();
}


void GameScene::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * Application::GetWindowWidth() / Application::GetWindowHeight();
	//Update Player
	Player::GetInstance()->update(dt);
	//Update enemies

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	{
		double x, y;
		MouseController::GetInstance()->GetMousePosition(x, y);
		float w = Application::GetWindowWidth();
		float h = Application::GetWindowHeight();
		float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
		float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
		Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);

		Enemy* e = EnemyManager::GetInstance()->get_inactive();
		e->active = true;
		e->init(cursor_point_in_world_space, Vector3(3, 3, 0), Vector3(0, 1, 0));
	}
	EnemyManager::GetInstance()->update(dt);

	//Update all hitbox entities
	DmgHitBoxManager::GetInstance()->update_all_hitbox(dt);
	//Update Physics
	PhysicsManager::GetInstance()->update(dt);
	//Update collisions
	CollisionManager::GetInstance()->update(dt);
	//update the show hp thing
	ShowHpManager::GetInstance()->update(dt);

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F1))
	{
		SceneManager::GetInstance()->setNextScene("Editor");
	}


	fps = 1.0 / dt;
	MyDebugger::GetInstance()->watch_this_info("fps", fps);
}


void GameScene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, worldWidth, 0, worldHeight, -10, 10);
	Graphics::GetInstance()->projectionStack.LoadMatrix(projection);

	// Camera matrix
	Graphics::GetInstance()->viewStack.LoadIdentity();
	Graphics::GetInstance()->viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	Graphics::GetInstance()->modelStack.LoadIdentity();

	MS& ms = Graphics::GetInstance()->modelStack;
	RenderHelper::RenderMesh(axis, false);

	ms.PushMatrix();
	RenderManager::GetInstance()->render_all_active_objects();

	ShowHpManager::GetInstance()->render_all_hp_text();
	RenderManager::GetInstance()->post_render();

	MyDebugger::GetInstance()->render_debug_info();
	//hax
#if DEBUGPLAYER
	Player::GetInstance()->render_debug();
#endif
	ms.PopMatrix();

}

void GameScene::Exit()
{

	PhysicsManager::Destroy();
	CollisionManager::Destroy();
	GameObjectManager::Destroy();
	//MeshList::Destroy();
	EnvironmentManager::Destroy();
	RenderManager::Destroy();

	ShowHpManager::GetInstance()->clear_hptext();
}

