#include "GameObjectManager.h"

#include "GameObject.h"
//#include <fstream>
#include <string>
#include <sstream>
#include "MeshList.h"
#include "EnvironmentManager.h"
#include "RenderManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for each (auto &g in game_object_list)
	{
		if (g)
			delete g;
	}
	game_object_list.clear();
}

GameObject * GameObjectManager::request_new(GameObjectType id)
{
	GameObject* temp = nullptr;
	switch (id)
	{

	}
	game_object_list.push_back(temp);
	return temp;
}

void GameObjectManager::load_objects(const char* file_path)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open()) {
		std::cout << "Impossible to open " << file_path << ". Are you in the right directory ?\n";
		return;
	}

	while (!fileStream.eof()) {
		char buf[256];
		fileStream.getline(buf, 256);
		std::string bufstr(buf);
		if (bufstr.find("#") != std::string::npos)
		{
			//check what isit
			if (bufstr.find("SETTINGS") != std::string::npos)
				load_settings(fileStream, bufstr);
			if (bufstr.find("OBJECTS") != std::string::npos)
				load_objects(fileStream, bufstr);

		}
	}

	fileStream.close();

	//update collider's AABB
	for each (auto &go in game_object_list)
	{
		//Collidable* temp_collidable = dynamic_cast<Collidable*>(go);
		//if (temp_collidable)
		//	temp_collidable->update_collider();
		
	}
}

void GameObjectManager::load_settings(std::ifstream& fileStream, std::string& bufstr)
{
	char buf[256];
	fileStream.getline(buf, 256);
	bufstr = buf;

	while (bufstr != "\r" && bufstr != "")//escape aka enter
	{
		if (strncmp("worldwidth", buf, 10) == 0)
		{
			size_t comma_index = bufstr.find('=');
			bufstr = bufstr.substr(comma_index + 1);
			//GameLogic::GetInstance()->set_world_width(std::stof(bufstr));//auto ignore \r
		}
		fileStream.getline(buf, 256);
		bufstr = buf;
	}
}

void GameObjectManager::load_objects(std::ifstream& fileStream, std::string& bufstr)
{
	char buf[256];
	fileStream.getline(buf, 256);
	bufstr = buf;

	//check semo id.
	int ID_index = 0;
	while (bufstr.find("ID") != std::string::npos)
	{
		//#ID <-4 chars
		size_t space_index = bufstr.find(" ");
		bufstr = bufstr.substr(space_index + 1);
		ID_index = std::stoi(bufstr);
		load_object(fileStream, bufstr, (GameObjectType)ID_index);

		fileStream.getline(buf, 256);
		bufstr = buf;
	}
}

void GameObjectManager::load_object(std::ifstream& fileStream, std::string& bufstr, GameObjectType id)
{
	//This functions determine which id is it in, and load all related objs
	//and determine whr to push the obj to. eg. physics manager/gamelogic
	char buf[256];
	fileStream.getline(buf, 256);
	bufstr = buf;

	while (bufstr != "\r" && bufstr != "")
	{
		GameObject* temp = nullptr;
		temp = this->request_new(id);
		switch (id)
		{
	
		}

		fileStream.getline(buf, 256);
		bufstr = buf;
	}

	
}

Vector3 GameObjectManager::get_vector3(std::ifstream& fileStream, std::string& bufstr)
{
	std::string temp;
	std::stringstream ss;
	ss.str(bufstr);
	getline(ss, temp, '=');
	Vector3 ret;
	
	if (temp == "pos")
		ret.Set(0, 0, 0);
	else if (temp == "scale")
		ret.Set(1, 1, 1);
	else {
		std::cerr << "MISSING TRANSFORM COMPONENT!" << std::endl;
		throw std::exception("MISSING TRANSFORM COMPONENT!");
	}
	

	getline(ss, temp, ',');
	if (temp == "\r")
		return ret;
	ret.x = std::stof(temp);
	getline(ss, temp, ',');
	ret.y = std::stof(temp);
	getline(ss, temp);
	ret.z = std::stof(temp);

	char buf[256];
	fileStream.getline(buf, 256);
	bufstr = buf;

	return ret;
}


void GameObjectManager::render_all_objects()
{
	for each (auto &obj in game_object_list)
	{
		if (obj)
			obj->render();
	}
}