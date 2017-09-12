#include "ParticleManager.h"
#include "MeshList.h"

#include "Graphics.h"
#include "RenderHelper.h"

void Particle::update(double dt)
{
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Fire"));
	if (sa)
	{
		sa->m_anim = &this->anim;
		sa->Update(dt);
	}

	active_elapsed += dt;
	

	if (active_elapsed >= active_duration)  // elapsed more than duration
	{
		this->active = false;
		active_elapsed = 0.0;
	}
}

void Particle::init()
{
	active_elapsed = 0.0;
	//SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Fire"));
	//if (sa)
	//{
	//	sa->m_anim = new Animation();
	//	sa->m_anim->Set(0, 5, 1, 10.0f, true);
	//}

	anim.Set(0, 5, 1, 10.0f, true);
}

void Particle::render()
{

	MS& ms = Graphics::GetInstance()->modelStack;
	SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(MeshList::GetInstance()->getMesh("Fire"));
	if (sa)
		sa->m_anim = &this->anim;
	ms.PushMatrix();
	ms.Translate(this->pos);
	ms.Rotate(Math::RadianToDegree(atan2(this->dir.y, this->dir.x)), 0, 0, 1);
	ms.Scale(this->scale);
	RenderHelper::RenderMesh(sa, false);
	//sa->Render();
	ms.PopMatrix();
	if (sa)
		sa->m_anim = nullptr;
}

void Particle::set_duration(double duration)
{
	this->active_duration = duration;
}
