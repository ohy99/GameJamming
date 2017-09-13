#ifndef _GLOBALMANAGER_H
#define _GLOBALMANAGER_H

#include "SingletonTemplate.h"

class GlobalVariables : public Singleton<GlobalVariables>
{
	friend Singleton;

public:
	float * worldWidth;
	float * worldHeight;

	float get_worldWidth() { return *worldWidth; }
	float get_worldHeight() { return *worldHeight; }
protected:
	GlobalVariables() : worldWidth(nullptr), worldHeight(nullptr) {}
	~GlobalVariables() {}
};



#endif