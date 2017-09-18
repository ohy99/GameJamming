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
	Faction(FACTION_SIDE side) : side(side) {}
	Faction() {}
};

#endif // !FACTION_H
