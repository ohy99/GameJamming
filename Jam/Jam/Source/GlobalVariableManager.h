#ifndef _GLOBALMANAGER_H
#define _GLOBALMANAGER_H

#include "SingletonTemplate.h"

class GlobalVariables : public Singleton<GlobalVariables>
{
	friend Singleton;

public:


protected:
	GlobalVariables() {}
	~GlobalVariables() {}
};



#endif