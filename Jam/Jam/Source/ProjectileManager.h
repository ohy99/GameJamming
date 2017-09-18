#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "SingletonTemplate.h"

#include <vector>
#include <map>
class Projectile;

class ProjectileManager : public Singleton<ProjectileManager>
{
public:
	enum PROJECTILE_TYPE
	{
		DEFAULT = 0
	};
private:
	friend Singleton;
	std::map< PROJECTILE_TYPE, std::vector<Projectile*> >projectile_list;

	void pool_vector(std::vector<Projectile*> & vec, Projectile* proj, unsigned int number = 100);
public:
	Projectile* get_projectile(PROJECTILE_TYPE type = PROJECTILE_TYPE::DEFAULT);
	void deactivate_all();
protected:
	ProjectileManager();
	~ProjectileManager();
};

#endif // !PROJECTILEMANAGER_H
