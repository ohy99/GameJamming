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

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Math::InitRNG();

	axis = MeshBuilder::GenerateAxes("", 100, 100, 100);


	worldHeight = 100;
	worldWidth = worldHeight * Application::GetWindowWidth() / Application::GetWindowHeight();
}


void GameScene::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * Application::GetWindowWidth() / Application::GetWindowHeight();
	//Update enemies
	//Update Physics
	//PhysicsManager::GetInstance()->update(dt);
	//Update collisions
	//CollisionManager::GetInstance()->update(dt);
	//update the show hp thing
	//ShowHpManager::GetInstance()->update(dt);

	fps = 1.0 / dt;

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

	ShowHpManager::Destroy();
}

