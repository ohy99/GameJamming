//GameScene_H


#ifndef GameScene_H
#define GameScene_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "AudioPlayer.h"
class Mesh;

class GameScene : public Scene, public MessageHandle
{
public:
	GameScene();
	~GameScene();

	void RenderBackground();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	virtual void Handle(BaseMessage* msg);

protected:
	Camera camera;
	double fps;
	//AudioPlayer audioPlayer;
	Mesh* axis;
	Mesh* backGround;

	bool dmg_up;
	bool fr_up;

	//Mesh* background;
	float worldHeight;
	float worldWidth;

	std::vector<GameObject*> backgroundObjects;
};

#endif