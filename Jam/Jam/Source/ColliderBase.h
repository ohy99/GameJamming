#ifndef COLLIDERBASE_H
#define COLLIDERBASE_H

/**********************************************************

	Need this so can hold pointer to collider template

***********************************************************/

class ColliderBase abstract
{
public:
	virtual bool check_collision(ColliderBase* other) = 0;
protected:
	ColliderBase() {}
	virtual ~ColliderBase() {}


};

#endif // !COLLIDERBASE_H

