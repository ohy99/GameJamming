#include "Options.h"
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
#include "MouseController.h"
#include "KeyboardController.h"

Options::Options()
{
}

Options::~Options()
{
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
	GameObjectManager::Destroy();
	MeshList::Destroy();
	EnvironmentManager::Destroy();
	RenderManager::Destroy();
}

void Options::Init()
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
	vol = 0;
	vol = (100 - audioPlayer.getCurrentVolume()) / 10;
	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	Math::InitRNG();

	axis = MeshList::GetInstance()->getMesh("MENUBACKGROUND");
	bar = MeshBuilder::GenerateQuad("", Color(1, 1, 1), 1);
	//background = EntityBase::getInstance()->getEntity("BACKGROUND");
	plusbutt.pos.Set(30, 15, 0);
	plusbutt.resize_button(10, 10);
	plusbutt.mesh = MeshList::GetInstance()->getMesh("PLUSBUTTON");
	minusbutt.pos.Set(-23, 15, 0);
	minusbutt.resize_button(10, 10);
	minusbutt.mesh = MeshList::GetInstance()->getMesh("MINUSBUTTON");
	bvolume.pos.Set(0, 35, 0);
	bvolume.resize_button(30, 15);
	bvolume.mesh= MeshList::GetInstance()->getMesh("VOLUME");
	instructions.pos.Set(0,-10, 0);
	instructions.resize_button(40, 15);
	instructions.mesh = MeshList::GetInstance()->getMesh("INSTRUCTIONS");
	back.pos.Set(35, -40, 0);
	back.resize_button(30, 15);
	back.mesh = MeshList::GetInstance()->getMesh("BACK");

	audioPlayer.playlist.push_back(new Sound("Audio//Level1.mp3"));
	audioPlayer.playlist.push_back(new Sound("Audio//explosion.wav"));

	audioPlayer.playSoundThreaded(audioPlayer.playlist[0]->fileName_);
}


void Options::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	double x, y;
	MouseController::GetInstance()->GetMousePosition(x, y);

	PhysicsManager::GetInstance()->update(dt);
	//Update collisions
	CollisionManager::GetInstance()->update(dt);

	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();

	fps = 1.0 / dt;
	//TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));
	Vector3 cursor_point_in_world_space(x / w * worldWidth - worldWidth * 0.5f, (Application::GetWindowHeight() - y) / h * worldHeight - worldHeight * 0.5f);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;

//	std::cout << "options:" << audioPlayer.getCurrentVolume() << std::endl;
	if (MouseController::GetInstance()->IsButtonPressed(0))
	{
		if (plusbutt.collision.isCollide(cursor_collider))
		{
			if (vol > 0)
			{
				--vol;
			}
			audioPlayer.increaseVolume();
		}
		if (minusbutt.collision.isCollide(cursor_collider))
		{
			if (vol<10)
			++vol;

			audioPlayer.decreaseVolume();
		}
		if (back.collision.isCollide(cursor_collider))
			SceneManager::GetInstance()->setNextScene("MAIN");
	}



}



void Options::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(-worldWidth * 0.5f, worldWidth * 0.5f, -worldHeight * 0.5f, worldHeight * 0.5f, -10, 10);
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
	ms.PushMatrix();
	ms.Scale(135, 100, 1);
	RenderHelper::RenderMesh(axis, false);
	ms.PopMatrix();
	ms.PushMatrix();
	ms.Translate(-10, 0, 0);
	for (int i = 0; i < 10 - vol; ++i)
	{
		ms.PushMatrix();
		ms.Translate(i * 3, i * 0.5f+12, 0);
		ms.Scale(3, 3 + i, 0);
		RenderHelper::RenderMesh(bar, false);
		ms.PopMatrix();
	}
	ms.PopMatrix();

	plusbutt.render_button();
	minusbutt.render_button();
	bvolume.render_button();
	instructions.render_button();
	back.render_button();
}

void Options::Exit()
{
	audioPlayer.pause();
	//if (axis)
	//{
	//	delete axis;
	//	axis = nullptr;
	//}


}
