#ifndef DIETODISTANCE_H
#define DIETODISTANCE_H

#include "DieCondition.h"
#include "MyMath.h"

class DieToDistance : public DieCondition
{
	float distance_travelled;
	float distance_dead;
	float move_speed;
public:
	virtual void update(double dt) { this->distance_travelled = Math::Min(distance_travelled + move_speed * (float)dt, distance_dead); }
	virtual bool is_dead() {
		return distance_travelled >= distance_dead;
	}
	DieToDistance(float distance, float move_spd) : distance_travelled(0.f), distance_dead(distance), move_speed(move_spd) {}
	~DieToDistance() {}
};

#endif // !DIETODISTANCE_H

