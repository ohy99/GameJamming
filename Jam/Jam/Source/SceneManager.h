#ifndef _SCENEMANAGER_H
#define _SCENEMANAGER_H

#include <map>
#include "Scene.h"
#include "SingletonTemplate.h"

class SceneManager : public Singleton <SceneManager>
{
	friend Singleton;
	bool shouldExit = false;
	std::map < std::string, Scene*> scenes;
	Scene* curr;
	SceneManager() {
	}
public:

	~SceneManager() {
		for each(auto p in scenes) {
			if (p.second)
			{
				p.second->Exit();
				delete p.second;
				p.second = nullptr;
			}
		}
	}
	void addScene(std::string key, Scene* a) {
		scenes[key] = a;
	}
	void update(double dt) {
		curr->Update(dt);
		curr->Render();
	}

	void setNextScene(std::string n) {
		curr->Exit();
		curr = scenes[n];
		curr->Init();
		curr->Update(0.0);
	}
	void setCurrScene(std::string a) {
		curr = scenes[a];
		curr->Init();
	}
	void setExitGame(bool a) {
		shouldExit = true;
	}
	bool checkShouldExit() {
		return shouldExit;
	}

	Scene* get_scene(std::string name) {
		return scenes.at(name);
	}
};

#endif
