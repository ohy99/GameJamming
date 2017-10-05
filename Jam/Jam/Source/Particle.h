#ifndef PARTICLE_H
#define PARTICLE_H

#include "GameObject.h"
#include "Physics.h"
class DieCondition;
class ParticleManager;
class Particle : public GameObject
{
	friend ParticleManager;
	DieCondition* dieCondition;
	Physics physic;
public:
	Particle();
	~Particle();
	void init(Vector3 pos, Vector3 dir, Vector3 scale, float speed, double active_duration = 1.0);
	void update(double dt);
	void deactivate();
};

#endif // !PARTICLE_H

