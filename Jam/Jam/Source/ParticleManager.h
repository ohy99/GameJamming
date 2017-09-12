#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "GameObject.h"
#include "SpriteAnimation.h"
class Particle : public GameObject
{
public:
	Animation anim;
	virtual void update(double dt);
	void init();
	virtual void render();
	Particle() {};
	~Particle() {};
	void set_duration(double duration);
private:
	double active_elapsed;
	double active_duration;

protected:
};

#endif // 
