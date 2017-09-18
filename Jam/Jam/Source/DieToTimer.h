#ifndef DIETOTIMER_H
#define DIETOTIMER_H

#include "DieCondition.h"
#include "MyTimer.h"

class DieToTimer : public DieCondition
{
	MyTimer timer;
public:
	virtual void update(double dt) { timer.update_timer(dt); }
	virtual bool is_dead() {
		return timer.is_Duration_Passed();
	}
	DieToTimer(float duration) { timer.set_duration(duration); }
	~DieToTimer() {}
};

#endif // !DIETODISTANCE_H

