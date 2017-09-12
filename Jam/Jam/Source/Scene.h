#ifndef SCENE_H
#define SCENE_H

class SceneManager;

class Scene
{
	friend SceneManager;
public:
	Scene() {}
	virtual ~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif