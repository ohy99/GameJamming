#ifndef POWERUP_H
#define POWERUP_H

#include "DmgHitBox.h"

class DmgHitBoxManager;
class DieCondition;
class PowerUp : public DmgHitBox
{
private:
	friend DmgHitBoxManager;

	DieCondition* die_condition;
public:
	PowerUp();
	PowerUp(const PowerUp& other);
	virtual ~PowerUp();
	virtual void update(double dt);

};

#endif // !POWERUP_H
