#include "GameFlowController.h"

#include "EnemyManager.h"
#include "KeyboardController.h"
//#include "Boss.h"
#include "MyDebugger.h"
#include "BossManager.h"

GameFlowController::GameFlowController() :
	max_wave_before_boss(3),
	currState(STATE(0)),
	prevState(STATE(0))
{
	EnemyManager::GetInstance()->set_max_wave(max_wave_before_boss);

	transition_timer.set_duration(2.0);
}

GameFlowController::~GameFlowController()
{
}

void GameFlowController::init()
{
	//called when start game scene
	currState = STATE::WAVE;
	prevState = STATE::WAVE;
	max_wave_before_boss = 3;
}

void GameFlowController::update(double dt)
{
	if (KeyboardController::GetInstance()->IsKeyPressed(VK_SPACE))
	{
		//EnemyManager::GetInstance()->reset_wave(false);
		change_state(STATE::TRANSITION);
	}
	if (KeyboardController::GetInstance()->IsKeyReleased(VK_SPACE))
	{
		//EnemyManager::GetInstance()->reset_wave(true);
	}

	check_change_in_state();
	update_state(dt);

	std::string state_text;
	switch (currState)
	{
	case WAVE:
		state_text = "WAVE";
		break;
	case TRANSITION:
		state_text = "TRANSITION";
		MyDebugger::GetInstance()->watch_this_info("transition time", transition_timer.get_current_percent());
		break;
	case BOSS:
		state_text = "BOSS";
		break;
	}
	MyDebugger::GetInstance()->watch_this_info("currState", state_text);
}

void GameFlowController::change_state(STATE state)
{
	prevState = currState;
	currState = state;

	//transitional function calls, exiting
	switch (prevState)
	{
	case WAVE:
		EnemyManager::GetInstance()->deactivate_all();
		break;
	case TRANSITION:
		transition_timer.reset_timer();
		break;
	case BOSS:
		BossManager::GetInstance()->Exit();
		break;
	}

	//transitional function calls, entering
	switch (state)
	{
	case WAVE:
		EnemyManager::GetInstance()->init();
		break;
	case TRANSITION:
		break;
	case BOSS:
		BossManager::GetInstance()->Init();
		break;
	}
}

void GameFlowController::check_change_in_state()
{
	//state all the conditions for the state change ;)
	switch (currState)
	{
	case STATE::WAVE:
	{
		if (EnemyManager::GetInstance()->is_wave_ended() && currState == STATE::WAVE)
		{
			change_state(STATE::TRANSITION);
		}
		break;
	}
	case STATE::TRANSITION:
	{
		if (transition_timer.is_Duration_Passed())
		{
			if (prevState == STATE::WAVE)
				change_state(STATE::BOSS);
			else
				change_state(STATE::WAVE);
		}
		break;
	}
	case STATE::BOSS:
	{
		if (BossManager::GetInstance()->IsBossDead() && currState == STATE::BOSS)
		{
			change_state(STATE::TRANSITION);
		}
		break;
	}
	}
}

void GameFlowController::update_state(double dt)
{
	switch (currState)
	{
	case STATE::WAVE:
		EnemyManager::GetInstance()->update(dt);
		break;
	case STATE::TRANSITION:
		transition_timer.update_timer(dt);
		break;
	case STATE::BOSS:
		BossManager::GetInstance()->Update(dt);
		break;
	}
}
