#include "PlayerCollisionResponse.h"

PlayerResponse::PlayerResponse()
{
}

PlayerResponse::~PlayerResponse()
{
}

bool PlayerResponse::response(GameObject * other, GameObject* my_owner)
{
	//dynamic cast to see who hit me
	//would usually work unless u try to cast to shishanth
	//because u cant see shishanth hitting u
	//jk :3
	return false;
}
