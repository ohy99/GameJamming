#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <map>
#include "SingletonTemplate.h"
class Scene;

class SceneManager : public Singleton <SceneManager>
{
	friend Singleton;
	bool shouldExit = false;
	std::map < std::string, Scene*> scenes;
	Scene* curr;
	SceneManager();

	//Called once at start
	void setCurrScene(std::string a);
public:

	~SceneManager();
	void addScene(std::string key, Scene* a);
	void update(double dt);

	void setNextScene(std::string n);
	void setExitGame(bool a);
	bool checkShouldExit();

	Scene* get_scene(std::string name);
};

#endif
