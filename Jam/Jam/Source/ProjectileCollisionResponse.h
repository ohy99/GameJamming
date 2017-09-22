#ifndef PROJECTILECOLLISIONRESPONSE_H
#define PROJECTILECOLLISIONRESPONSE_H

#include "DamageHitCollisionResponse.h"

class ProjectileResponse : public DamageHitResponse
{
	bool is_collided;
public:
	ProjectileResponse();
	virtual ~ProjectileResponse();

	virtual bool response(GameObject* other, GameObject* my_owner);
	virtual void reset_response();

	bool get_isCollided() { return is_collided; }
};


#endif // !PROJECTILECOLLISIONRESPONSE_H

