#ifndef PLAYERCOLLISIONRESPONSE_H
#define PLAYERCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class PlayerResponse : public CollisionResponse
{
public:
	PlayerResponse();
	~PlayerResponse();

	virtual void response(GameObject* other);
};


#endif // !PLAYERCOLLISIONRESPONSE_H

