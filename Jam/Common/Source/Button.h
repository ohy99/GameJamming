#ifndef BUTTON_H
#define BUTTON_H

#include "Collision.h"
#include "Mesh.h"
#include "Graphics.h"
#include "RenderHelper.h"

struct Button
{
	Collision collision;

	Mesh* mesh;
	Vector3 pos;
	Vector3 scale;
	Vector3 dir;
	Button() {
		pos.Set(0, 0, 0);
		scale.Set(1, 1, 1);
		dir.Set(0, 1, 0);
		mesh = nullptr;
		collision.mid = &this->pos;
		collision.collisionType = Collision::CollisionType::AABB;
		collision.min.Set(-scale.x*0.5f, -scale.y*0.5f);
		collision.max.Set(scale.x*0.5f, scale.y*0.5f);
	}

	void resize_button(float scalex, float scaley) {
		scale.Set(scalex, scaley);
		collision.min.Set(-scale.x*0.5f, -scale.y*0.5f);
		collision.max.Set(scale.x*0.5f, scale.y*0.5f);
	}

	void render_button()
	{
		MS& ms = Graphics::GetInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(this->pos);
		ms.Scale(this->scale);
		RenderHelper::RenderMesh(this->mesh, false);
		ms.PopMatrix();
	}

};


#endif