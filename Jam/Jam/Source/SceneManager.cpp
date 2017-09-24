#include "SceneManager.h"

#include "GameScene.h"
#include "Mainmenu.h"
#include "Options.h"
#include "EditorScene.h"

SceneManager::SceneManager() {
	//init everything here
	this->addScene("GAME", new GameScene());
	this->addScene("MAIN", new Mainmenu());
	this->addScene("OPTIONS", new Options());
	this->addScene("Editor", new EditorScene());

	this->setCurrScene("GAME");

}

SceneManager::~SceneManager() {
	for each(auto p in scenes) {
		if (p.second)
		{
			p.second->Exit();
			delete p.second;
			p.second = nullptr;
		}
	}
	scenes.clear();
}

void SceneManager::addScene(std::string key, Scene * a) {
	scenes[key] = a;
}

void SceneManager::update(double dt) {
	curr->Update(dt);
	curr->Render();
}

void SceneManager::setNextScene(std::string n) {
	curr->Exit();
	curr = scenes[n];
	curr->Init();
	curr->Update(0.0);
}

void SceneManager::setCurrScene(std::string a) {
	curr = scenes[a];
	curr->Init();
}

void SceneManager::setExitGame(bool a) {
	shouldExit = a;
}

bool SceneManager::checkShouldExit() {
	return shouldExit;
}

Scene * SceneManager::get_scene(std::string name) {
	return scenes.at(name);
}
