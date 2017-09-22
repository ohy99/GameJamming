#ifndef AOECOLLISIONRESPONSE_H
#define AOECOLLISIONRESPONSE_H

#include "DamageHitCollisionResponse.h"
#include <set>

class AOEResponse : public DamageHitResponse
{
	typedef std::set<GameObject*> set_type;
	typedef set_type::iterator Iter;
	set_type collided;//store pointers of collided objects

	void clear_collided();
public:
	AOEResponse();
	virtual ~AOEResponse();

	virtual bool response(GameObject* other, GameObject* my_owner);
	virtual void reset_response();
};


#endif // !AOECOLLISIONRESPONSE_H

