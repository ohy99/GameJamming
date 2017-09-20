#ifndef CHARACTERBASE_H
#define CHARACTERBASE_H

#include "HitPoints.h"
#include "Faction.h"
class CharacterBase
{
public:
	HitPoint hitpoint;
	Faction faction;
	virtual ~CharacterBase() {}
protected:
	CharacterBase() {}
};


#endif // !CHARACTERBASE_H

