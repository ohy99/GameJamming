#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include "SingletonTemplate.h"
#include <map>

class InputController : public Singleton<InputController>
{
	friend Singleton<InputController>;
	enum CONTROLLER_TYPE
	{
		KEYBOARD,
		MOUSE
	};
public:
	enum PLAYER_INPUT
	{
		MOVE_FRONT,
		MOVE_BACK,
		MOVE_LEFT,
		MOVE_RIGHT,

		SHOOT,
		MELEE,
		DASH
	};
private:
	std::map <PLAYER_INPUT, std::pair<CONTROLLER_TYPE, unsigned char> > input_map;
public:
	bool isInputPressed(PLAYER_INPUT input);
	bool isInputDown(PLAYER_INPUT input);
	bool isInputReleased(PLAYER_INPUT input);
	bool isInputUp(PLAYER_INPUT input);
	
	void init(const char* file_path = nullptr);
protected:
	InputController();
	~InputController();
};

#endif // !INPUTCONTROLLER_H

