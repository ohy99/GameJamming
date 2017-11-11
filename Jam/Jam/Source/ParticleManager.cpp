#include "ParticleManager.h"

#include "Particle.h"
#include "RenderManager.h"
#include "MeshList.h"
#include "MatrixStack.h"
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

void ParticleManager::spawn_particle(TYPE type, Vector3 pos, Vector3 dir)
{
	switch (type)
	{
	case BULLET_TRAIL:
	{
		int rand_num = Math::RandIntMinMax(-1, 2);
		for (int i = 0; i < rand_num; ++i)
		{
			Particle* p = this->get_inactive();
			if (p == nullptr)
				return;

			float angle = Math::RandFloatMinMax(-30.f, 30.f);
			Mtx44 rotation;
			rotation.SetToRotation(angle, 0, 0, 1);
			Vector3 rdir = -dir;
			rdir = rotation * rdir;

			float spd = Math::RandFloatMinMax(10.0f, 15.f);
			float dura = Math::RandFloatMinMax(0.25f, 0.5f);
			p->init(pos, rdir, Vector3(Math::RandFloatMinMax(0.5f, 1.0f), 0.5f, 1.f), spd, dura);
			p->mesh = MeshList::GetInstance()->getMesh("YellowQuad");
		}
		break;
	}
	case CLICKFORFUN:
	{
		int rand_num = Math::RandIntMinMax(1, 3);
		for (int i = 0; i < rand_num; ++i)
		{
			Particle* p = this->get_inactive();
			if (p == nullptr)
				return;

			float angle = Math::RandFloatMinMax(-30.f, 30.f);
			Mtx44 rotation;
			rotation.SetToRotation(angle, 0, 0, 1);
			Vector3 rdir = -dir;
			rdir = rotation * rdir;
			if (rdir.IsZero())
			{
				rdir.Set(Math::RandFloat(), Math::RandFloat());
				try {
					rdir.Normalize();
				}
				catch (DivideByZero) {
					rdir.Set(1, 0, 0);
				}
			}

			float spd = Math::RandFloatMinMax(10.0f, 15.f);
			float dura = Math::RandFloatMinMax(0.25f, 0.5f);
			p->init(pos, rdir, Vector3(Math::RandFloatMinMax(0.5f, 1.0f), 0.5f, 1.f), spd, dura);
			int randmesh = Math::RandIntMinMax(0, 6);
			if (randmesh == 0)
				p->mesh = MeshList::GetInstance()->getMesh("Quad");
			else if (randmesh == 1)
				p->mesh = MeshList::GetInstance()->getMesh("RedQuad");
			else if (randmesh == 2)
				p->mesh = MeshList::GetInstance()->getMesh("GreenQuad");
			else if (randmesh == 3)
				p->mesh = MeshList::GetInstance()->getMesh("BlueQuad");
			else if (randmesh == 4)
				p->mesh = MeshList::GetInstance()->getMesh("YellowYellQuad");
			else if (randmesh == 5)
				p->mesh = MeshList::GetInstance()->getMesh("PurpleQuad");
			else if (randmesh == 6)
				p->mesh = MeshList::GetInstance()->getMesh("TurqQuad");
		}
	}
		break;
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
