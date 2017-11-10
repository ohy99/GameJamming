#include "ParticleManager.h"

#include "Particle.h"
#include "RenderManager.h"
#include "MeshList.h"
ParticleManager::ParticleManager()
{
	for (int i = 0; i < 500; ++i)
	{
		Particle* p = new Particle();
		particle_pool.push_back(p);
		
	}
}
ParticleManager::~ParticleManager()
{
	for (auto p : particle_pool)
	{
		delete p;
		p = nullptr;
	}
	particle_pool.clear();
	active_particle.clear();
}

void ParticleManager::update(double dt)
{
	for (std::list<Particle*>::iterator it = active_particle.begin(); it != active_particle.end();)
	{
		Particle* p = (*it);
		p->update(dt);
		if (!p->active)
		{
			//if particle deactivated by die condition
			it = active_particle.erase(it);
		}
		else
			++it;
	}
}

void ParticleManager::spawn_particle(TYPE type, Vector3 pos)
{
	switch (type)
	{
	case HIT_ENEMY:
	{
		int rand_num = Math::RandIntMinMax(3, 7);
		for (int i = 0; i < rand_num; ++i)
		{
			Particle* p = this->get_inactive();
			if (p == nullptr)
				return;

			Vector3 dir(Math::RandFloatMinMax(-1, 1), Math::RandFloatMinMax(-1, 1), 0);
			try {
				dir.Normalize();
			}
			catch (DivideByZero) {
				dir.Set(0, 1, 0);
			}
			p->init(pos, dir, Vector3(0.25f, 0.5f, 1.f), 7.5f, 1.0);
			p->mesh = MeshList::GetInstance()->getMesh("Quad");
		}
		break;
	}
	case DEADPLAYER:
	{
		int rand_num = Math::RandIntMinMax(20, 30);
		for (int i = 0; i < rand_num; ++i)
		{
			Particle* p = this->get_inactive();
			if (p == nullptr)
				return;

			Vector3 dir(Math::RandFloatMinMax(-1, 1), Math::RandFloatMinMax(-1, 1), 0);
			try {
				dir.Normalize();
			}
			catch (DivideByZero) {
				dir.Set(0, 1, 0);
			}
			float spd = Math::RandFloatMinMax(5.0f, 15.f);
			float dura = Math::RandFloatMinMax(1.0f, 5.0f);
			p->init(pos, dir, Vector3(1.0f, 2.0f, 1.f), spd, dura);
			p->mesh = MeshList::GetInstance()->getMesh("RedQuad");
		}
		break;
	}
		
	}
}

Particle * ParticleManager::get_inactive()
{
	for each (auto &p in particle_pool)
	{
		if (!p->active)
		{
			p->active = true;
			active_particle.push_back(p);
			return p;
		}
	}
	return nullptr;
}
