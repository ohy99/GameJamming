#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class GameObject;
#include <fstream>
#include "Vector3.h"

//Manages the life time of GameObjects
class GameObjectManager : public Singleton<GameObjectManager>
{
	friend Singleton;

	std::vector<GameObject*> game_object_list;

	void load_settings(std::ifstream& file, std::string& bufstr);
	void load_objects(std::ifstream& file, std::string& bufstr);
public:
	enum GameObjectType {
		//#ID IS NUMERICAL ASCENDING.
		//Define the types of game objects here.
		PLAYERTOWER = 0,
		ENEMYTOWER,
		//Backgrounds & Tiles
		BACKGROUND,
		TILES,
		BACKGROUND2,
		TILES2,
		BACKGROUND3,
		TILES3,
		BACKGROUND4,
		TILES4,
		//Enemies
		ENEMY1,
		ENEMY2,

		/*PLAYERTOWER2,
		ENEMYTOWER1,
		ENEMYTOWER2,*/
	};
	GameObject* request_new(GameObjectType);

	void load_objects(const char* file_name);
	void render_all_objects();
protected:
	GameObjectManager();
	~GameObjectManager();

private:
	void load_object(std::ifstream& fileStream, std::string& bufstr, GameObjectType id);
	Vector3 get_vector3(std::ifstream& fileStream, std::string& bufstr);
};

#endif // !GAMEOBJECTMANAGER_H
