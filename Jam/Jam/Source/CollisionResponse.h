#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

class GameObject;
class CollisionResponse
{
public:
	virtual bool response(GameObject* other, GameObject* my_owner) = 0;
	virtual void reset_response() {}

	CollisionResponse(){}
	virtual ~CollisionResponse() {}
};

#endif // !COLLISION_RESPONSE_H

