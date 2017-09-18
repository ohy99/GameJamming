#include "ProjectileManager.h"

#include "Projectile.h"
#include "Collider.h"
#include "ProjectileCollisionResponse.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "DmgHitBox.h"

//*******************************************************************
//
//	NOTE: projectiles here all have 0 dmg even after pooled
//
//*******************************************************************
ProjectileManager::ProjectileManager()
{
	Projectile* default_proj = new Projectile;
	default_proj->scale.Set(1, 1, 0);
	default_proj->collider = new Collider<ProjectileResponse>(default_proj);
	default_proj->collider->set(Collision::CollisionType::SPHERE, &default_proj->pos, default_proj->scale.x);
	default_proj->mesh = MeshList::GetInstance()->getMesh("Sphere");
	pool_vector(projectile_list[DEFAULT] , default_proj);
}

ProjectileManager::~ProjectileManager()
{
	for each (auto m in projectile_list)
	{
		for each (auto v in m.second)
		{
			delete v;
		}
		m.second.clear();
	}
}

void ProjectileManager::pool_vector(std::vector<Projectile*>& vec, Projectile* proj, unsigned int number)
{
	if (proj == nullptr)//aint gona store 100 nullptrs for u man
		return;

	vec.push_back(proj);
	RenderManager::GetInstance()->attach_renderable(proj);
	//number -1 coz 1 is there ^
	for (unsigned int i = 0; i < number - 1; ++i) {
		Projectile* temp_proj = new Projectile(*proj);
		vec.push_back(temp_proj);

		RenderManager::GetInstance()->attach_renderable(temp_proj);
	}
}

Projectile* ProjectileManager::get_projectile(PROJECTILE_TYPE type)
{
	for (const auto &m : projectile_list.at(type))
	{
		if (!m->active)
			return m;
	}
	return nullptr;
}

void ProjectileManager::deactivate_all()
{
	for each (auto &m in projectile_list)
	{
		for each (auto &v in m.second)
			v->active = false;
		
	}
}
