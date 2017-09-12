#include "GameObject.h"

#include "Graphics.h"
#include "RenderHelper.h"

GameObject::GameObject() :
	active(false),
	mesh(nullptr),
	pos(0,0,0),
	scale(1,1,1),
	dir(0,1,0)
{
}

GameObject::~GameObject()
{
}

void GameObject::render()
{
	MS& ms = Graphics::GetInstance()->modelStack;

	ms.PushMatrix();
	ms.Translate(this->pos);
	ms.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x))- 90.f, 0, 0, 1);
	ms.Scale(this->scale);
	RenderHelper::RenderMesh(this->mesh, false);
	ms.PopMatrix();
}
void GameObject::update(double dt)
{

}