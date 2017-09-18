#include "InputController.h"

#include "KeyboardController.h"
#include "MouseController.h"

InputController::InputController()
{
}

InputController::~InputController()
{
}

bool InputController::isInputPressed(PLAYER_INPUT input)
{
	switch (input_map.at(input).first)
	{
	case CONTROLLER_TYPE::MOUSE:
		return MouseController::GetInstance()->IsButtonPressed(input_map.at(input).second);
	default:
		return KeyboardController::GetInstance()->IsKeyPressed(input_map.at(input).second);
	}
	return false;
}

bool InputController::isInputDown(PLAYER_INPUT input)
{
	switch (input_map.at(input).first)
	{
	case CONTROLLER_TYPE::MOUSE:
		return MouseController::GetInstance()->IsButtonDown(input_map.at(input).second);
	default:
		return KeyboardController::GetInstance()->IsKeyDown(input_map.at(input).second);
	}
	return false;
}

bool InputController::isInputReleased(PLAYER_INPUT input)
{
	switch (input_map.at(input).first)
	{
	case CONTROLLER_TYPE::MOUSE:
		return MouseController::GetInstance()->IsButtonReleased(input_map.at(input).second);
	default:
		return KeyboardController::GetInstance()->IsKeyReleased(input_map.at(input).second);
	}
	return false;
}

bool InputController::isInputUp(PLAYER_INPUT input)
{
	switch (input_map.at(input).first)
	{
	case CONTROLLER_TYPE::MOUSE:
		return MouseController::GetInstance()->IsButtonUp(input_map.at(input).second);
	default:
		return KeyboardController::GetInstance()->IsKeyUp(input_map.at(input).second);
	}
	return false;
}

void InputController::init(const char * file_path)
{
	if (file_path != nullptr)
	{
		//open file
	}
	else
	{
		input_map[PLAYER_INPUT::MOVE_FRONT] = std::make_pair(CONTROLLER_TYPE::KEYBOARD, 'W');
		input_map[PLAYER_INPUT::MOVE_BACK ] = std::make_pair(CONTROLLER_TYPE::KEYBOARD, 'S');
		input_map[PLAYER_INPUT::MOVE_LEFT] = std::make_pair(CONTROLLER_TYPE::KEYBOARD, 'A');
		input_map[PLAYER_INPUT::MOVE_RIGHT] = std::make_pair(CONTROLLER_TYPE::KEYBOARD, 'D');

		input_map[PLAYER_INPUT::SHOOT] = std::make_pair(CONTROLLER_TYPE::MOUSE, 0);
		input_map[PLAYER_INPUT::MELEE] = std::make_pair(CONTROLLER_TYPE::MOUSE, 1);
		input_map[PLAYER_INPUT::DASH] = std::make_pair(CONTROLLER_TYPE::KEYBOARD, VK_SPACE);
	}
}
