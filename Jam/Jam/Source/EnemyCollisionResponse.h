#ifndef ENEMYCOLLISIONRESPONSE_H
#define ENEMYCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class EnemyResponse : public CollisionResponse
{
public:
	EnemyResponse();
	virtual ~EnemyResponse();

	virtual bool response(GameObject* other, GameObject* my_owner);
};


#endif // !ENEMYCOLLISIONRESPONSE_H

