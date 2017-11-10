#include "Mainmenu.h"
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
#include "KeyboardController.h"
#include "MouseController.h"

Mainmenu::Mainmenu()
{
	axis = nullptr;
}

Mainmenu::~Mainmenu()
{
	PhysicsManager::Destroy();
	CollisionManager::Destroy();
}

void Mainmenu::Init()
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

	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	worldWidth = worldHeight * 4.f / 3.f;

	Math::InitRNG();

	//axis = MeshList::GetInstance()->getMesh("MENUBACKGROUND");

	Vector3 middle_pt(worldWidth * 0.5f, worldHeight * 0.5f);

	Button* temp = new Button();
	temp->mesh = MeshList::GetInstance()->getMesh("Quad");
	temp->pos = middle_pt;
	temp->default_scale.Set(35, 10);
	temp->resize_button(temp->default_scale);

	buttons.insert(std::make_pair("GAME", temp));

	MouseController::GetInstance()->SetKeepMouseCentered(false);
	next_scene = nullptr;
	feedback_timer.set_duration(0.5);
	feedback_timer.reset_timer();

	AudioPlayer::GetInstance()->PlayBackground2D("Pim Poy", 0.2);
}


void Mainmenu::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	double x, y;
	MouseController::GetInstance()->GetMousePosition(x, y);

	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	//std::cout << float(x / w * worldWidth) << std::endl;
	fps = 1.0 / dt;
	//TextManager::GetInstance()->add_text(0, "fps: " + std::to_string(fps));

	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	Collision cursor_collider;
	cursor_collider.collisionType = Collision::POINT;
	cursor_collider.mid = &cursor_point_in_world_space;


	for each (auto &butt in buttons)
	{
		if (butt.second->collision.isCollide(cursor_collider))
		{
			if (MouseController::GetInstance()->IsButtonPressed(MouseController::LMB))
			{
				butt.second->is_triggered = true;
			}
			else if (MouseController::GetInstance()->IsButtonDown(MouseController::LMB))
			{
				butt.second->is_triggered = true;
				butt.second->scale.Set(butt.second->default_scale.x * 0.9f, butt.second->default_scale.y * 0.95f);
			}
			else if (MouseController::GetInstance()->IsButtonReleased(MouseController::LMB) && butt.second->is_triggered)
			{
				//switch scene babi
				next_scene = &butt.first;
				//got is triggered because if u click outside and release on the button, this shit will trigger
				//this bool  prevents it from happening
				butt.second->is_triggered = false;
			}
			else if (MouseController::GetInstance()->IsButtonUp(MouseController::LMB))
			{
				butt.second->resize_button(butt.second->default_scale.x * 1.1f, butt.second->default_scale.y * 1.2f);
			}
		}
		else
		{
			butt.second->is_triggered = false;
			butt.second->resize_button(butt.second->default_scale);
		}
	}
	
	if (next_scene)
	{
		//next scene set alr
		feedback_timer.update_timer(dt);

		if (feedback_timer.is_Duration_Passed())
		{
			SceneManager::GetInstance()->setNextScene(*next_scene);
		}
	}


}



void Mainmenu::Render()
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
	ms.PushMatrix();
	//ms.Scale(135, 100, 1);
	RenderHelper::RenderMesh(axis, false);
	ms.PopMatrix();


	for each (auto &butt in buttons)
	{
		butt.second->render_button();
	}
}

void Mainmenu::Exit()
{
	//audioPlayer.pause();

	//delete all buttons
	for each (auto butt in buttons)
	{
		delete butt.second;
		butt.second = nullptr;
	}
	buttons.clear();
	next_scene = nullptr;

}
