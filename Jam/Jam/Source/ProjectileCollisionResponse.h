#ifndef PROJECTILECOLLISIONRESPONSE_H
#define PROJECTILECOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class ProjectileResponse : public CollisionResponse
{
public:
	ProjectileResponse();
	~ProjectileResponse();

	virtual void response(GameObject* other);
};


#endif // !PROJECTILECOLLISIONRESPONSE_H

