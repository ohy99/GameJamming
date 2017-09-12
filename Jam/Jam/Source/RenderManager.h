#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <map>

class GameObject;

class RenderManager :public Singleton<RenderManager>
{
	friend Singleton;
	std::map<int, std::vector<GameObject*> >objects;
	GameObject* last_to_render;
public:
	void attach_renderable(GameObject* , int layer = 0);
	void render_all_active_objects();
	void post_render();
	void render_this_last(GameObject* obj);
	GameObject * remove_renderable(GameObject* obj);
protected:
	RenderManager();
	~RenderManager();
};

#endif // !RENDERMANAGER_H
