#ifndef DMGHITBOXMANAGER_H
#define DMGHITBOXMANAGER_H

#include "SingletonTemplate.h"

#include <vector>
#include <map>
class DmgHitBox;
class Mesh;
class DmgHitBoxManager : public Singleton<DmgHitBoxManager>
{
public:
	enum DMG_COLLIDER_TYPE
	{
		PROJECTILE = 0,
		MELEE,
		BOSS_PROJ,
		DC_COUNT
	};
private:
	friend Singleton;
	//std::map< DMG_COLLIDER_TYPE, std::vector<DmgHitBox*> >projectile_list;
	Mesh* dmg_hitbox_mesh[DC_COUNT];
	std::vector<DmgHitBox*> hit_box_pool;
	void pool_vector(std::vector<DmgHitBox*> & vec, DmgHitBox* hitbox, unsigned int number = 100);

	//Here set the hitbox to pre-defined scaling
	void set_hitbox(DmgHitBox& hitbox, DMG_COLLIDER_TYPE type);
public:
	DmgHitBox* get_hitbox(DMG_COLLIDER_TYPE type);
	void deactivate_all();
	void update_all_hitbox(double dt);
protected:
	DmgHitBoxManager();
	~DmgHitBoxManager();
};


#endif // !DMGHITBOXMANAGER_H

