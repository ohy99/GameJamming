#ifndef GAMEFLOWCONTROLLER_H
#define GAMEFLOWCONTROLLER_H

#include "SingletonTemplate.h"
#include "MyTimer.h"

class GameFlowController : public Singleton<GameFlowController>
{
public:
	enum STATE
	{
		WAVE,
		TRANSITION,
		BOSS
	};
	STATE currState, prevState;
	void init();
	void update(double dt);
private:
	friend Singleton;
	int max_wave_before_boss;
	MyTimer transition_timer;

	void change_state(STATE state);
	void check_change_in_state();
	void update_state(double dt);
protected:
	GameFlowController();
	~GameFlowController();
};

#endif // !GAMEFLOWCONTROLLER_H

