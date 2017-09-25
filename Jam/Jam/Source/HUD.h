#ifndef HUD_H
#define HUD_H

#include "SingletonTemplate.h"

class HUD : public Singleton <HUD>
{
	friend Singleton;

public:
	void render();
protected:
	HUD();
	~HUD();
};

#endif // !HUD_H

