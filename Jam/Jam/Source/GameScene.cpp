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
#include "CameraManager.h"
#include "HUD.h"
#include "Loader.h"
#include "ParticleManager.h"
#include "GameFlowController.h"
#include "MessageDispatcher.h"
#include "ConcreteMessage.h"

#include "GLFW\glfw3.h"
#include "GL\glew.h"
#include "Application.h"

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
	HUD::Destroy();
	Loader::Destroy();
	ParticleManager::Destroy();
	GameFlowController::Destroy();
}

void GameScene::RenderBackground()
{
	float scaleX = 2000 / 1000;

	static int frame = 0;
	static float bg1X = worldWidth* 0.5f * scaleX;
	static float bg2X = worldWidth* 1.5f * scaleX;

	++frame;

	float movement = 0.5;

	if (bg1X < scaleX *worldWidth* -0.5f)
		bg1X = bg2X + scaleX * worldWidth;
	if (bg2X < scaleX *worldWidth* -0.5f)
		bg2X = bg1X + scaleX *worldWidth;

	MS& ms = Graphics::GetInstance()->modelStack;
	ms.PushMatrix();
	ms.Translate(bg1X -= movement, worldHeight * 0.5f, 0);
	ms.Scale(scaleX*worldWidth, worldHeight, 1);
	RenderHelper::RenderMesh(backGround, false);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Translate(bg2X -= movement, worldHeight * 0.5f, 0);
	ms.Scale(scaleX*worldWidth, worldHeight, 1);
	RenderHelper::RenderMesh(backGround, false);
	ms.PopMatrix();

	if (frame >= 30) {
		int chanceForAsteroid = Math::RandIntMinMax(0, 100);
		if (chanceForAsteroid <= 10) {
			GameObject* go = nullptr;
			for (auto it : backgroundObjects) {
				if (!it->active) {
					go = it;
					break;
				}
			}
			if (go == nullptr)
				return;
			float scale = Math::RandFloatMinMax(5, 20);
			go->scale.Set(scale, scale, 1);
			float vel = Math::RandFloatMinMax(0.2, 0.5);
			go->dir.Set(-vel, 0, 0);
			float y = Math::RandFloatMinMax(0, worldHeight);
			go->pos.Set(worldWidth + scale * 272 / 80, y, 1);
			go->active = true;
		}
		frame = 0;
	}
	for (auto it : backgroundObjects) {
		if (it->active) {
			ms.PushMatrix();
			ms.Translate(it->pos.x += it->dir.x, it->pos.y, 0);
			ms.Scale(it->scale.x * 272 / 80, it->scale.y, 1);
			RenderHelper::RenderMesh(it->mesh, false);
			ms.PopMatrix();

			if (it->pos.x < -it->scale.x * 272 / 80)
				it->active = false;
		}
	}
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
	CameraManager::GetInstance()->attach_camera(&camera);

	axis = MeshBuilder::GenerateAxes("", 100, 100, 100);
	backGround = MeshList::GetInstance()->getMesh("sky 2");

	worldHeight = 100;
	worldWidth = worldHeight * Application::GetWindowWidth() / Application::GetWindowHeight();

	GlobalVariables::GetInstance()->worldWidth = &this->worldWidth;
	GlobalVariables::GetInstance()->worldHeight = &this->worldHeight;
	//Player init must be called after this 2 lines. because world width and height is used (for now)
	InputController::GetInstance()->init();//insert file here
	Player::GetInstance()->init();

	MessageDispatcher::GetInstance()->Register("GameScene", this);

	//ProjectileManager::GetInstance();
	EnemyManager::GetInstance()->init();
	DmgHitBoxManager::GetInstance();
	ShowHpManager::GetInstance();
	ParticleManager::GetInstance();
	GameFlowController::GetInstance()->init();

	//Cursor										GLFW_CURSOR 0x00033001   GLFW_CURSOR_HIDDEN 0x00034002
	glfwSetInputMode(Application::GetInstance().getWindowPtr(), 0x00033001, 0x00034002);

	for (int i = 0; i < 10; ++i) {
		GameObject* go = new GameObject();
		go->mesh = MeshList::GetInstance()->getMesh("Meteor");
		backgroundObjects.push_back(go);
	}

	fr_up = dmg_up = false;
	crediting = false;
}


void GameScene::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * Application::GetWindowWidth() / Application::GetWindowHeight();
	//Update Player
	Player::GetInstance()->update(dt);
	//Update enemies
	GameFlowController::GetInstance()->update(dt);
	//EnemyManager::GetInstance()->update(dt);

	//Update all hitbox entities
	DmgHitBoxManager::GetInstance()->update_all_hitbox(dt);
	//Update Physics
	PhysicsManager::GetInstance()->update(dt);
	//Update collisions
	CollisionManager::GetInstance()->update(dt);
	//update the show hp thing
	ShowHpManager::GetInstance()->update(dt);
	CameraManager::GetInstance()->update(dt);
	ParticleManager::GetInstance()->update(dt);

	//debug purposes
	/*if (KeyboardController::GetInstance()->IsKeyPressed('P')) {
		MessageDispatcher::GetInstance()->Send("MachineGun", new MessageWeapon(MessageWeapon::APPLY_FIRERATE_BOOST));
	}
	if (KeyboardController::GetInstance()->IsKeyPressed('B')) {
		MessageDispatcher::GetInstance()->Send("MachineGun", new MessageWeapon(MessageWeapon::APPLY_DAMAGE_BOOST));
	}*/
	if (KeyboardController::GetInstance()->IsKeyDown('C')) {
		crediting = true;
	}
	else {
		crediting = false;
	}

	if (Player::GetInstance()->GetDead()) {
		if (KeyboardController::GetInstance()->IsKeyPressed(VK_RETURN)) {
			SceneManager::GetInstance()->setNextScene("MAIN");
		}
	}

	if (KeyboardController::GetInstance()->IsKeyPressed(VK_F1))
	{
		SceneManager::GetInstance()->setNextScene("Editor");
	}

	MessageDispatcher::GetInstance()->Send("MachineGun", new MessageCheckBuff());
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

	RenderBackground();
	

	RenderManager::GetInstance()->render_all_active_objects();

	ShowHpManager::GetInstance()->render_all_hp_text();
	RenderManager::GetInstance()->post_render();
	HUD::GetInstance()->render();

	if (dmg_up) {
		MS& ms = Graphics::GetInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(worldWidth * 0.5f, worldHeight * 0.5, 3);
		ms.Scale(worldWidth, worldHeight, 1);
		RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("damage up"), false);
		ms.PopMatrix();
		dmg_up = false;
	}
	if (fr_up) {
		MS& ms = Graphics::GetInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(worldWidth * 0.5f, worldHeight * 0.5, 1);
		ms.Scale(worldWidth, worldHeight, 1);
		RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("firerate up"), false);
		ms.PopMatrix();
		fr_up = false;
	}
	if (crediting) {
		MS& ms = Graphics::GetInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(worldWidth * 0.5f, worldHeight * 0.5, 3);
		ms.Scale(worldWidth, worldHeight / 2, 1);
		RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("credit"), false);
		ms.PopMatrix();
	}

	if (Player::GetInstance()->GetDead()) {
		MS& ms = Graphics::GetInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(worldWidth * 0.5f, worldHeight * 0.5, 1);
		ms.Scale(worldWidth * 0.8f, worldHeight * 0.8f, 1);
		RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("death scene"), false);
		ms.PopMatrix();
	}

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

	for (auto it : backgroundObjects) {
		delete it;
		it = nullptr;
	}
	backgroundObjects.clear();
}

void GameScene::Handle(BaseMessage * msg)
{
	MessageCheckBuff* messageCheckBuff = dynamic_cast<MessageCheckBuff*>(msg);
	if (messageCheckBuff) {
		if (messageCheckBuff->bol)
		{
			if (messageCheckBuff->type == MessageCheckBuff::CHECK_DAMAGE) {
				dmg_up = true;
			}
			else {
				fr_up = true;
			}
		}
		delete messageCheckBuff;
		return;
	}
	delete msg;
}

