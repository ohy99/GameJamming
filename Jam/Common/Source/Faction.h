#ifndef FACTION_H
#define FACTION_H

struct Faction
{
	enum FACTION_SIDE
	{
		NONE,
		PLAYER,
		ENEMY
	}side = NONE;
};

#endif // !FACTION_H
