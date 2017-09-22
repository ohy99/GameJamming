#include "ProjectileCollisionResponse.h"

#include "GameObject.h"
#include "DmgHitBox.h"

ProjectileResponse::ProjectileResponse() : is_collided(false)
{
}

ProjectileResponse::~ProjectileResponse()
{
}

bool ProjectileResponse::response(GameObject * other, GameObject * my_owner)
{
	if (is_collided)
		return false;

	if (DamageHitResponse::response(other, my_owner))
	{
		//additional property
		//cannot call set_inactive() because it will remove from collisionmanager and fk up the loop
		//DmgHitBox* dhb = dynamic_cast<DmgHitBox*>(my_owner);
		//if (dhb)
		//	dhb->set_inactive();

		is_collided = true;
		return true;
	}


	return false;
}

void ProjectileResponse::reset_response()
{
	this->is_collided = false;
}
