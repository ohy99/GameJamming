#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "Mesh.h"
#include "MessageHandle.h"

class GameObject : public MessageHandle
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
	virtual void Handle(BaseMessage* msg) {}
};

#endif