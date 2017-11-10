#ifndef BOSSBASE_H
#define BOSSBASE_H

class BossBase
{
public:
	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Exit() = 0;
	virtual bool IsDead() = 0;
};

#endif // !BOSSBASE_H

