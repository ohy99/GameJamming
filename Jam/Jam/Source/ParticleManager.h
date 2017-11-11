#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
#include <list>
#include "Vector3.h"
class Particle;
class ParticleManager : public Singleton<ParticleManager>
{
public:
	enum TYPE
	{
		HIT_ENEMY,
		DEADPLAYER,
		BULLET_TRAIL,
	};
private:
	friend Singleton;
	std::vector<Particle*> particle_pool;
	std::list<Particle*> active_particle;

	//returns active = true particle
	Particle* get_inactive();
public:
	void update(double dt);

	void spawn_particle(TYPE type, Vector3 pos);
	void spawn_particle(TYPE type, Vector3 pos, Vector3 dir);
protected:
	ParticleManager();
	~ParticleManager();
};

#endif // 
