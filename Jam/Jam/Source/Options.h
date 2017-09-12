#ifndef OPTIONS_H
#define OPTIONS_H

#include "GameObject.h"
#include <vector>
#include "Scene.h"
#include "Camera.h"
#include "Button.h"
#include "AudioPlayer.h"

class Mesh;

class Options : public Scene
{
public:
	Options();
	~Options();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

protected:
	Camera camera;
	double fps;
	Button plusbutt;
	Button minusbutt;
	Button instructions;
	Button bvolume;
	Button back;
	Mesh* axis;
	Mesh* bar;
	int vol;
	AudioPlayer audioPlayer;
	//Mesh* background;
	float worldHeight;
	float worldWidth;
};

#endif