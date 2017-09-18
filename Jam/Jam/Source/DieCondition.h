#ifndef DIECONDITION_H
#define DIECONDITION_H

class DieCondition abstract
{
public:
	virtual void update(double dt) = 0;
	virtual ~DieCondition() {}
	virtual bool is_dead() = 0;
protected:
	DieCondition() {}
};


#endif // !DIECONDITION_H

