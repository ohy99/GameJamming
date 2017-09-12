#ifndef _HPBAR_H
#define _HPBAR_H

#include "Graphics.h"
#include "RenderHelper.h"
#include "SingletonTemplate.h"
#include "Vector3.h"
#include "MeshList.h"

class HpBar : public Singleton<HpBar>
{
	friend Singleton;
	Mesh* redBar;
	Mesh* greenBar;
	//float hpPercent;
	HpBar() {
		redBar = MeshList::GetInstance()->getMesh("REDHPBAR");
		greenBar = MeshList::GetInstance()->getMesh("GREENHPBAR");
	}
public:
	Vector3 pos;
	Vector3 scale;

	virtual ~HpBar() {
	}

	void update(float hpPercent) {

	}

	void render(float hpPercent = 1.f) {

		MS& ms = Graphics::GetInstance()->modelStack;
		ms.PushMatrix();
		ms.Translate(this->pos.x, this->pos.y, this->pos.z);
		//Graphics::getInstance()->modelStack.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)) - 90.f, 0, 0, 1);
		ms.PushMatrix();
		ms.Scale(this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(redBar, false);
		ms.PopMatrix();

		ms.PushMatrix();
		ms.Translate(-(1.f - hpPercent) * this->scale.x * 0.5f, 0, 0);
		ms.Scale(hpPercent * this->scale.x, this->scale.y, this->scale.z);
		RenderHelper::RenderMesh(greenBar, false);
		ms.PopMatrix();

		ms.PopMatrix();
	}
};

#endif