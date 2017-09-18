#include "DmgHitBoxManager.h"

#include "DmgHitBox.h"
#include "Projectile.h"
#include "Collider.h"
#include "ProjectileCollisionResponse.h"
#include "MeshList.h"
#include "RenderManager.h"
#include "DmgHitBox.h"
#include "DieToDistance.h"
#include "DieToTimer.h"

void DmgHitBoxManager::pool_vector(std::vector<DmgHitBox*>& vec, DmgHitBox * hitbox, unsigned int number)
{
	if (hitbox == nullptr)//aint gona store 100 nullptrs for u man
		return;

	vec.push_back(hitbox);
	RenderManager::GetInstance()->attach_renderable(hitbox);
	//number -1 coz 1 is there ^
	for (unsigned int i = 0; i < number - 1; ++i) {
		DmgHitBox* temp_hitbox = new DmgHitBox(*hitbox);
		vec.push_back(temp_hitbox);

		RenderManager::GetInstance()->attach_renderable(temp_hitbox);
	}
}

void DmgHitBoxManager::set_hitbox(DmgHitBox& hitbox, DMG_COLLIDER_TYPE type)
{
	switch (type)
	{
	case PROJECTILE:
		hitbox.scale.Set(1, 1, 1);
		if (!dynamic_cast<Collider<ProjectileResponse>*>(hitbox.collider))//if not the collider i want
		{
			if (hitbox.collider)//if got something
				delete hitbox.collider;
			hitbox.collider = new Collider<ProjectileResponse>(static_cast<GameObject*>(&hitbox));
		}
		hitbox.get_collider_component()->set(Collision::CollisionType::SPHERE, &hitbox.pos, hitbox.scale.x);
		break;
	case MELEE:
		hitbox.scale.Set(5, 5, 1);
		if (!dynamic_cast<Collider<ProjectileResponse>*>(hitbox.collider))//if not the collider i want
		{
			if (hitbox.collider)//if got something
				delete hitbox.collider;
			hitbox.collider = new Collider<ProjectileResponse>(static_cast<GameObject*>(&hitbox));
		}
		hitbox.get_collider_component()->set(Collision::CollisionType::AABB, &hitbox.pos, -hitbox.scale * 0.5f, hitbox.scale * 0.5f);
		break;
	default:
		hitbox.scale.Set(1, 1, 1);
		//hitbox.get_collider_component()->set(Collision::CollisionType::SPHERE, &hitbox.pos, hitbox.scale.x);
	}
}

DmgHitBox * DmgHitBoxManager::get_hitbox(DMG_COLLIDER_TYPE type)
{
	for (const auto &m : hit_box_pool)
	{
		if (!m->active)
		{
			m->mesh = dmg_hitbox_mesh[type];
			this->set_hitbox(*m, type);
			return m;
		}
	}
	return nullptr;
}

void DmgHitBoxManager::deactivate_all()
{
	for each (auto &m in hit_box_pool)
	{
		m->set_inactive();
	}
}

void DmgHitBoxManager::update_all_hitbox(double dt)
{
	for each (auto &hb in hit_box_pool)
	{
		if (hb->active)
			hb->update(dt);
	}
}

DmgHitBoxManager::DmgHitBoxManager()
{
	DmgHitBox* default_hitbox = new DmgHitBox;
	default_hitbox->scale.Set(1, 1, 0);
	default_hitbox->collider = new Collider<ProjectileResponse>(default_hitbox);
	default_hitbox->get_collider_component()->set(Collision::CollisionType::SPHERE, &default_hitbox->pos, default_hitbox->scale.x);
	//default_hitbox->mesh = MeshList::GetInstance()->getMesh("Sphere");

	dmg_hitbox_mesh[DEFAULT] = MeshList::GetInstance()->getMesh("Sphere");
	dmg_hitbox_mesh[PROJECTILE] = MeshList::GetInstance()->getMesh("Sphere");
	dmg_hitbox_mesh[MELEE] = MeshList::GetInstance()->getMesh("Quad");
	pool_vector(hit_box_pool, default_hitbox);
}

DmgHitBoxManager::~DmgHitBoxManager()
{
	for each (auto m in hit_box_pool)
	{
		delete m;
	}
}
