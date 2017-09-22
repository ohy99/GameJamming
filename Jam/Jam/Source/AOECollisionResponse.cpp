#include "AOECollisionResponse.h"

#include "CharacterBase.h"

AOEResponse::AOEResponse()
{
}

AOEResponse::~AOEResponse()
{
}

bool AOEResponse::response(GameObject * other, GameObject* my_owner)
{
	std::pair<Iter, bool> ret;
	ret = collided.insert(other);

	//if inserted successfully ;)
	if (ret.second)
		if (DamageHitResponse::response(other, my_owner))
			return true;
	

	return false;
}

void AOEResponse::reset_response()
{
	this->clear_collided();
}

void AOEResponse::clear_collided()
{
	collided.clear();
}
