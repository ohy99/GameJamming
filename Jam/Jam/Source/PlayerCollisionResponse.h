#ifndef PLAYERCOLLISIONRESPONSE_H
#define PLAYERCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class PlayerResponse : public CollisionResponse
{
public:
	PlayerResponse();
	virtual ~PlayerResponse();

	virtual bool response(GameObject* other, GameObject* my_owner);
};


#endif // !PLAYERCOLLISIONRESPONSE_H

