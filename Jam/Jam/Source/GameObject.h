#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "Mesh.h"

class GameObject
{
public:
	Mesh* mesh;

	Vector3 pos;
	Vector3 dir;
	Vector3 scale;
	
	bool active;

	GameObject();
	virtual ~GameObject();

	virtual void render();
	virtual void update(double dt);
};

#endif