#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "Button.h"
#include "AudioPlayer.h"
#include <map>
#include "MyTimer.h"
class Mesh;

class Mainmenu : public Scene
{
public:
	Mainmenu();
	~Mainmenu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;

	Mesh* axis;

	MyTimer mouseParticleTimer;
	Vector3 prevCursor;
	std::map<std::string , Button*> buttons;
	MyTimer feedback_timer;
	const std::string* next_scene;
	//AudioPlayer audioPlayer;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
};

#endif