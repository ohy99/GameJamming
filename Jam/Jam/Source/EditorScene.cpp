#include "EditorScene.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

#include "MeshList.h"
#include "RenderHelper.h"
#include "Graphics.h"

#include "GlobalVariableManager.h"
#include "MeshBuilder.h"
#include "SceneManager.h"

#include "MouseController.h"
#include "KeyboardController.h"
#include "FontTypeManager.h"
#include "MyDebugger.h"
#include <fstream>
#include <stdio.h> 
#include "Loader.h"

EditorScene::EditorScene() : 
	start_of_pattern("============ Pattern ============"),
	end_of_pattern("========== Pattern End ==========")
{
}

EditorScene::~EditorScene()
{
}

void EditorScene::Init()
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


	node = MeshList::GetInstance()->getMesh("node");
	highlight = MeshList::GetInstance()->getMesh("node_highlight");
	node_scale.Set(3, 3, 1);
	current_path = 0;
	current_pattern = 0;
	current_action = ACTION::CREATE_NEW_PAT;
}

void EditorScene::Update(double dt)
{
	worldHeight = 100;
	worldWidth = worldHeight * Application::GetWindowWidth() / Application::GetWindowHeight();
	//fixed ratio
	worldWidth = worldHeight * 4.f / 3.f;

	if (current_action == ACTION::CREATE_NEW_PAT)
	{
		update_create_new_pattern();
		if (KeyboardController::GetInstance()->IsKeyPressed(VK_TAB))
		{
			clear_unsaved_pattern();
			load_pattern();
			current_action = ACTION::VIEW_PAT;
		}
	}
	else if (current_action == ACTION::VIEW_PAT)
	{
		update_view_patterns();
		if (KeyboardController::GetInstance()->IsKeyPressed(VK_TAB))
		{
			clear_loaded_pattern();
			current_action = ACTION::CREATE_NEW_PAT;
		}
	}

	fps = 1.0 / dt;
}

void EditorScene::Render()
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

	if (current_action == ACTION::CREATE_NEW_PAT)
	{
		render_create_new_pattern();
	}
	else
	{
		render_view_patterns();
	}


	MyDebugger::GetInstance()->render_debug_info();
}

void EditorScene::update_create_new_pattern()
{
	double x, y;
	MouseController::GetInstance()->GetMousePosition(x, y);
	float w = Application::GetWindowWidth();
	float h = Application::GetWindowHeight();
	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	Vector3 cursor_point_in_world_space(x / w * worldWidth, (Application::GetWindowHeight() - y) / h * worldHeight);
	Collision cursor_collider(Collision::CollisionType::POINT);
	cursor_collider.mid = &cursor_point_in_world_space;

	if (MouseController::GetInstance()->IsButtonPressed(0))
	{

		//add node
		Collision new_collision(Collision::CollisionType::AABB);
		new_collision.mid = new Vector3(cursor_point_in_world_space);
		new_collision.min = -node_scale* 0.5f;
		new_collision.max = node_scale* 0.5f;

		if (current_path >= unsaved_pattern.size())
			unsaved_pattern.push_back(upattern());

		std::list< upattern>::iterator path_iter = unsaved_pattern.begin();
		std::advance(path_iter, current_path);
		(*path_iter).push_back(new_collision);

	}
	else if (MouseController::GetInstance()->IsButtonPressed(1) && unsaved_pattern.size())
	{
		std::list< upattern>::iterator path_iter = unsaved_pattern.begin();
		std::advance(path_iter, current_path);
		if (path_iter != unsaved_pattern.end())
		{
			for (upattern::reverse_iterator it = (*path_iter).rbegin(); it != (*path_iter).rend(); ++it)
			{
				if (cursor_collider.isCollide((*it)))
				{
					//delete that collider
					(*path_iter).erase(--it.base());
					break;
				}
			}

		}

	}

	//switching of paths
	double change = MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET);
	if (change < 0.0)
	{
		//< 0.0 means pull down scroll wheel
		current_path = Math::Wrap(current_path + 1, 0, (int)unsaved_pattern.size());
		MouseController::GetInstance()->ResetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET);
	}
	else if (change > 0.0)
	{
		//>0.0 == push up scroll wheel
		current_path = Math::Wrap(current_path - 1, 0, (int)unsaved_pattern.size());
		MouseController::GetInstance()->ResetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET);
	}


	if (unsaved_pattern.size())
	{
		if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
		{
			//save
			save_pattern();
		}
		if (KeyboardController::GetInstance()->IsKeyPressed('R'))
		{
			//reset
			clear_unsaved_pattern();
		}
	}

	MyDebugger::GetInstance()->watch_this_info("Number Of Paths", unsaved_pattern.size());
	if (current_path >= unsaved_pattern.size())
		MyDebugger::GetInstance()->watch_this_info("Current Path", "NEW!");
	else
		MyDebugger::GetInstance()->watch_this_info("Current Path", current_path + 1);

}

void EditorScene::render_create_new_pattern()
{
	int path_iter_counter = 0;
	for (std::list<upattern>::iterator path_iter = unsaved_pattern.begin(); path_iter != unsaved_pattern.end(); ++path_iter, ++path_iter_counter)
	{
		upattern_iter prev_it = (*path_iter).begin();
		for (upattern_iter it = (*path_iter).begin(); it != (*path_iter).end(); ++it)
		{
			MS& ms = Graphics::GetInstance()->modelStack;

			Vector3 prev_pos = *(*prev_it).mid;
			Vector3 curr_pos = *(*it).mid;
			Vector3 dir = (-prev_pos + curr_pos);
			Vector3 rotate_about(0, 0, 1);
			float angle = 0;
			try {
				rotate_about = Vector3(1, 0, 0).Cross(dir.Normalized()).Normalize();
				angle = Vector3(1, 0, 0).Dot(dir.Normalized());

				angle = Math::RadianToDegree(acos(angle));
			}
			catch (DivideByZero) {
				angle = 0;
			}
			ms.PushMatrix();
			ms.Translate(dir * 0.5f + prev_pos);
			ms.Rotate(angle, rotate_about);
			ms.Scale(dir.Length() * 0.5f - node_scale.x * 0.5f);
			RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("REDLINE"), false);
			ms.PopMatrix();

			if (path_iter == std::next(unsaved_pattern.begin(), current_path))
			{
				ms.PushMatrix();
				ms.Translate(*(*it).mid);
				ms.Scale(node_scale);
				RenderHelper::RenderMesh(highlight, false);
				ms.PopMatrix();
			}
			ms.PushMatrix();
			ms.Translate(*(*it).mid);
			ms.Scale(node_scale);
			RenderHelper::RenderMesh(node, false);
			ms.PopMatrix();
			if (it == (*path_iter).begin())
			{
				float half_width = 0.f;
				FontType* font = &FontTypeManager::GetInstance()->get_font(FontTypeManager::CALIBRI);
				std::string str = std::to_string(path_iter_counter + 1);
				for (int i = 0; i < str.size(); ++i)
					half_width += font->textWidth[(int)str.at(i)];
				half_width *= 0.5f;

				ms.PushMatrix();
				ms.Translate((*(*it).mid).x, (*(*it).mid).y - node_scale.y * 0.5f, 1);
				ms.Scale(node_scale);
				ms.Translate(-half_width, 0, 0);
				RenderHelper::RenderText(font, str, Color(0, 1, 0));
				ms.PopMatrix();
			}

			//assign prev_it so i can find the previous guy
			prev_it = it;
		}// END OF CURRENT PATH

	}// END OF PATTERN


	if (unsaved_pattern.size())
	{
		MS& ms = Graphics::GetInstance()->modelStack;

		//i wan centralize da text
		float half_width = 0.f;
		FontType* font = &FontTypeManager::GetInstance()->get_font(FontTypeManager::CALIBRI);
		std::string save_str = "PRESS SPACE TO SAVE";
		for (int i = 0; i < save_str.size(); ++i)
			half_width += font->textWidth[(int)save_str.at(i)];

		half_width *= 0.5f;

		ms.PushMatrix();
		ms.Translate(worldWidth* 0.5f, 2.5f, 0);
		ms.Scale(5, 5, 1);
		ms.Translate(-half_width, 0, 0);
		RenderHelper::RenderText(font, save_str, Color(0, 1, 0));
		ms.PopMatrix();

		half_width = 0.f;
		save_str = "PRESS R TO RESET";
		for (int i = 0; i < save_str.size(); ++i)
			half_width += font->textWidth[(int)save_str.at(i)];

		half_width *= 0.5f;

		ms.PushMatrix();
		ms.Translate(worldWidth* 0.5f, 0.f, 0);
		ms.Scale(2.5f, 2.5f, 1);
		ms.Translate(-half_width, 0, 0);
		RenderHelper::RenderText(font, save_str, Color(0, 1, 0));
		ms.PopMatrix();
	}
}

void EditorScene::update_view_patterns()
{
	double change = MouseController::GetInstance()->GetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET);
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_DELETE))
	{
		delete_pattern(current_pattern);
	}
	else
	{
		if (change < 0.0)
		{
			//< 0.0 means pull down scroll wheel
			current_pattern = Math::Wrap(current_pattern + 1, 0, (int)loaded_pattern.size() - 1);
			MouseController::GetInstance()->ResetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET);
		}
		else if (change > 0.0)
		{
			//>0.0 == push up scroll wheel
			current_pattern = Math::Wrap(current_pattern - 1, 0, (int)loaded_pattern.size() - 1);
			MouseController::GetInstance()->ResetMouseScrollStatus(MouseController::SCROLL_TYPE::SCROLL_TYPE_YOFFSET);
		}
	}

	MyDebugger::GetInstance()->watch_this_info("Number Of Patterns", loaded_pattern.size());
	MyDebugger::GetInstance()->watch_this_info("Current Pattern", current_pattern + 1);
}

void EditorScene::render_view_patterns()
{
	if (!loaded_pattern.size())
		return;
	current_pattern = Math::Wrap(current_pattern, 0, (int)loaded_pattern.size() - 1);

	for (int path_index = 0; path_index < loaded_pattern.at(current_pattern).size(); ++path_index)
	{
		Vector3 prev_pos = loaded_pattern.at(current_pattern).at(path_index).at(0);//first guy
		for (int node_index = 0; node_index != loaded_pattern.at(current_pattern).at(path_index).size(); ++node_index)
		{
			MS& ms = Graphics::GetInstance()->modelStack;

			//Vector3 prev_pos = *(*prev_it).mid;
			Vector3 curr_pos = loaded_pattern.at(current_pattern).at(path_index).at(node_index);
			Vector3 dir = (-prev_pos + curr_pos);
			Vector3 rotate_about(0, 0, 1);
			float angle = 0;
			try {
				rotate_about = Vector3(1, 0, 0).Cross(dir.Normalized()).Normalize();
				angle = Vector3(1, 0, 0).Dot(dir.Normalized());

				angle = Math::RadianToDegree(acos(angle));
			}
			catch (DivideByZero) {
				angle = 0;
			}
			ms.PushMatrix();
			ms.Translate(dir * 0.5f + prev_pos);
			ms.Rotate(angle, rotate_about);
			ms.Scale(dir.Length() * 0.5f - node_scale.x * 0.5f);
			RenderHelper::RenderMesh(MeshList::GetInstance()->getMesh("REDLINE"), false);
			ms.PopMatrix();

			ms.PushMatrix();
			ms.Translate(curr_pos);
			ms.Scale(node_scale);
			RenderHelper::RenderMesh(node, false);
			ms.PopMatrix();
			if (node_index == 0)
			{
				float half_width = 0.f;
				FontType* font = &FontTypeManager::GetInstance()->get_font(FontTypeManager::CALIBRI);
				std::string str = std::to_string(path_index + 1);
				for (int i = 0; i < str.size(); ++i)
					half_width += font->textWidth[(int)str.at(i)];
				half_width *= 0.5f;

				ms.PushMatrix();
				ms.Translate(curr_pos.x, curr_pos.y - node_scale.y * 0.5f, 1);
				ms.Scale(node_scale);
				ms.Translate(-half_width, 0, 0);
				RenderHelper::RenderText(font, str, Color(0, 1, 0));
				ms.PopMatrix();
			}

			//assign prev_it so i can find the previous guy
			prev_pos = curr_pos;
		}// END OF CURRENT PATH

	}// END OF PATTERN
	
}


void EditorScene::save_pattern(char* file_path)
{
	//binary : open in binary. app : all output operations are performed at the end of the file
	std::ofstream fileStream(file_path, std::ios::binary | std::ios::app);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return;
	}

	fileStream << start_of_pattern;
	//int path_iter_counter = 0;
	for (std::list<upattern>::iterator path_iter = unsaved_pattern.begin(); path_iter != unsaved_pattern.end(); ++path_iter)
	{
		fileStream << '\n';
		for (upattern_iter it = (*path_iter).begin(); it != (*path_iter).end(); ++it)
		{
			fileStream << *((*it).mid) << std::endl;
		}
	}
	fileStream << end_of_pattern + "\n";

	fileStream.close();

	clear_unsaved_pattern();
}

void EditorScene::load_pattern(char * file_path)
{
	clear_unsaved_pattern();

	Loader::GetInstance()->load_pattern(loaded_pattern);
	return;

	//binary : open in binary. app : all output operations are performed at the end of the file
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return;
	}

	int current_pattern_index = 0;
	int current_path_index = 0;
	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
		if (strncmp(start_of_pattern.c_str(), buf, start_of_pattern.size()) == 0)
		{
			//sscanf_s((buf + 11), "%d", &charWidth);
			load_this_pattern(fileStream, buf);
		}
	}


	fileStream.close();
}

void EditorScene::load_this_pattern(std::ifstream & fileStream, char * buf)
{
	//mark the start of pattern
	loaded_pattern.push_back(lpat_pattern());
	while (std::strcmp(buf, (end_of_pattern).c_str()) != 0)
	{
		fileStream.getline(buf, 256);
		load_this_path(fileStream, buf);
	}
}

void EditorScene::load_this_path(std::ifstream & fileStream, char * buf)
{

	//if (strncmp(start_of_pattern.c_str(), buf, start_of_pattern.size()) == 0)

	Vector3 temp;

	loaded_pattern.back().push_back(lpat_path());
	lpat_path* current_path = &loaded_pattern.back().back();

	while (std::strlen(buf) > 0 && std::strcmp(buf, (end_of_pattern).c_str()) != 0)
	{
		if (sscanf_s((buf), "[ %f, %f, %f ]", &temp.x, &temp.y, &temp.z) == 3)
		{
			current_path->push_back(temp);
			fileStream.getline(buf, 256);
		}
	}
	

}

void EditorScene::delete_pattern(unsigned int index, char* file_path)
{

	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return;
	}

	if (!loaded_pattern.size())
	{
		std::cout << "There is nothing loaded!\n";
		return;
	}
	if (index > loaded_pattern.size())
	{
		std::cout << "Invalid Index to delete!\n";
		return;
	}
	
	loaded_pattern.erase(loaded_pattern.begin() + index);
	//clear temp.txt
	std::ofstream temp_fileStream("Image//temp.txt", std::ios::binary | std::ofstream::trunc);
	temp_fileStream.close();

	for (unsigned int pattern_index = 0; pattern_index < loaded_pattern.size(); ++pattern_index)
	{
		clear_unsaved_pattern();

		for (unsigned int path_index = 0; path_index < loaded_pattern.at(pattern_index).size(); ++path_index)
		{
			unsaved_pattern.push_back(upattern());//new path;
			std::list <upattern>::iterator upat_iter = std::next(unsaved_pattern.begin(), path_index);

			for (unsigned int node_index = 0; node_index < loaded_pattern.at(pattern_index).at(path_index).size(); ++node_index)
			{
				Vector3 node_pos = loaded_pattern.at(pattern_index).at(path_index).at(node_index);
				Collision node_collider;
				//just need to push pos
				node_collider.mid = new Vector3(node_pos);

				(*upat_iter).push_back(node_collider);
			}
		}
		
		//save pattern
		save_pattern("Image//temp.txt");
	}


	//havent close filestream. handling temp.txt and saved file
	fileStream.close();
	if (std::remove("Image//enemy_spawn_pattern.txt") == 0)
		std::cout << "SUCCESSFULLY DELETED " << "Image//enemy_spawn_pattern.txt" << std::endl;
	else
		std::cout << "ERROR DELETING " << "Image//enemy_spawn_pattern.txt" << std::endl;
	
	if (std::rename("Image//temp.txt", "Image//enemy_spawn_pattern.txt") == 0)
		std::cout << "SUCCESSFULLY RENAMED " << "Image//temp.txt" << " to " << "Image//enemy_spawn_pattern.txt" << std::endl;
	else
		std::cout << "ERROR RENAMING " << "Image//temp.txt" << " to " << "Image//enemy_spawn_pattern.txt" << std::endl;

	if(std::remove("Image//temp.txt"))
		std::cout << "SUCCESSFULLY DELETED " << "Image//temp.txt" << std::endl;
	else
		std::cout << "ERROR DELETING " << "Image//temp.txt" << std::endl;

	clear_loaded_pattern();
	load_pattern();
	current_pattern = Math::Clamp((int)index, 0, (int)loaded_pattern.size());
}

void EditorScene::Exit()
{
	clear_unsaved_pattern();
}

void EditorScene::clear_unsaved_pattern()
{
	for (std::list<upattern>::iterator path_iter = unsaved_pattern.begin(); path_iter != unsaved_pattern.end(); ++path_iter)
	{
		for (upattern_iter it = (*path_iter).begin(); it != (*path_iter).end(); ++it)
		{
			delete (*it).mid;
		}
	}
	unsaved_pattern.clear();

	current_path = 0;
}

void EditorScene::clear_loaded_pattern()
{
	loaded_pattern.clear();
	current_pattern = 0;
}
