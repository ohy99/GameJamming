#include "RenderManager.h"

#include "GameObject.h"
#include <exception>
#include "EnvironmentManager.h"
#include "Player.h"

RenderManager::RenderManager() : last_to_render(nullptr)
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::render_all_active_objects()
{
	//EnvironmentManager::GetInstance()->render_environment();

	for each (auto &gopair in objects)
	{
		//if (go->active)
		for each (auto &go in gopair.second) {
			if (!dynamic_cast<Player*>(go))
				go->render();
		}
	}
	if (Player::GetInstance()->active)
		Player::GetInstance()->render();
}

void RenderManager::post_render()
{
	if (last_to_render)
		if (last_to_render->active)
			last_to_render->render();
	last_to_render = nullptr;
}

void RenderManager::render_this_last(GameObject * obj)
{
	last_to_render = obj;
}

GameObject * RenderManager::remove_renderable(GameObject * obj)
{
	for each (auto &gopair in objects)
	{
		for (std::list<GameObject*>::iterator it = objects.at(gopair.first).begin();
			it != objects.at(gopair.first).end(); ++it)
			if ((*it) == obj)
			{
				GameObject* ret = *it;
				it = objects.at(gopair.first).erase(it);
				return ret;
			}
	}
}

void RenderManager::attach_renderable(GameObject* go, int layer)
{
	if (go == nullptr)
		throw std::exception("DONT TRY TO RENDER NULL PLS!");
	this->objects[layer].push_back(go);
}