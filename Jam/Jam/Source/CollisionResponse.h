#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

class GameObject;
class CollisionResponse
{
public:
	virtual void response(GameObject* other) = 0;
};

#endif // !COLLISION_RESPONSE_H

