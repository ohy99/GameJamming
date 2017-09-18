#ifndef AOEMANAGER_H
#define AOEMANAGER_H

#include "SingletonTemplate.h"

#include <vector>
#include <map>
class Projectile;

class AOEManager : public Singleton<AOEManager>
{
public:
	enum AOE_TYPE
	{
		MELEE = 0
	};
private:
	friend Singleton;
	std::map< AOE_TYPE, std::vector<Projectile*> >projectile_list;

	void pool_vector(std::vector<Projectile*> & vec, Projectile* proj, unsigned int number = 100);
public:
	Projectile* get_aoe(AOE_TYPE type = AOE_TYPE::MELEE);
	void deactivate_all();
protected:
	AOEManager();
	~AOEManager();
};

#endif // !PROJECTILEMANAGER_H
