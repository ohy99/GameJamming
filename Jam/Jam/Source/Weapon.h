#ifndef WEAPON_H
#define WEAPON_H

#include "GameObject.h"
#include "DamageEjector.h"
#include "MyTimer.h"
//#include "ProjectileManager.h"
#include "Physics.h"
#include "Faction.h"
#include "AudioPlayer.h"

#include "DmgHitBoxManager.h"
class Weapon : public GameObject
{
protected:
	DamageEjector damage;						//min - max dmg
	MyTimer attackspeed_timer;					//attspd
	DmgHitBoxManager::DMG_COLLIDER_TYPE proj_type;//type ejected
	Physics power;								//force / spd of proj ejected
	Faction faction;							//which side this belongs to
public:
	std::string name;

	Weapon();
	virtual ~Weapon();
	virtual void update(double dt);

	virtual void discharge() = 0;
	void set(int min_dmg, int max_dmg, double attacks_per_sec, DmgHitBoxManager::DMG_COLLIDER_TYPE type, float force, Faction::FACTION_SIDE side);
};

#endif // !WEAPON_H

