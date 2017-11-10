#include "PowerUp.h"

#include "DieToTimer.h"

PowerUp::PowerUp()
{
	this->die_condition = new DieToTimer(10.0);
}

PowerUp::PowerUp(const PowerUp & other)
{
}

PowerUp::~PowerUp()
{
}

void PowerUp::update(double dt)
{
	this->die_condition->update(dt);
}
