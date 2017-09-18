#ifndef MYTIMER_H
#define MYTIMER_H

#include "MyMath.h"

class MyTimer
{
	double elapsed_time;
	double duration;
public:
	MyTimer() : elapsed_time(0.0), duration(0.0) {}
	~MyTimer() {}
	void set_duration(double duration) { this->duration = duration; }
	void update_timer(double dt) { elapsed_time = Math::Min(elapsed_time + dt, duration); }
	bool is_Duration_Passed() { return elapsed_time >= duration; }
	void reset_timer() { elapsed_time = 0.0; }
};

#endif // !MYTIMER_H

