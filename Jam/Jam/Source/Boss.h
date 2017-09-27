#ifndef BOSS_H
#define BOSS_H

#include <map>

#include "SingletonTemplate.h"
#include "BasePart.h"

class Boss : public Singleton<Boss>{
	friend Singleton<Boss>;
public:
	Boss();
	~Boss();

	enum SIDE {
		DEFAULT = 0,
		LEFT = 1,
		MIDDLE = 2,
		RIGHT = 3
	};

	void update(double dt);

	bool RegisterPart(BasePart* part, SIDE side);

private:
	std::map<std::string, BasePart*> leftParts;
	std::map<std::string, BasePart*> middleParts;
	std::map<std::string, BasePart*> rightParts;

	BasePart* leftPart;
	BasePart* middlePart;
	BasePart* rightPart;
};

#endif