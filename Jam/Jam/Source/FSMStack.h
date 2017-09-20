#ifndef FSMSTACK_H
#define FSMSTACK_H

#include <stack>
#include "StateBase.h"

class FSMStack
{
	std::stack<StateBase*> state_stack;
public:
	void run_current(double dt);
	void push_state(StateBase* state);
	void pop_state();
	FSMStack();
	~FSMStack();
};


#endif // !FSMSTACK_H

