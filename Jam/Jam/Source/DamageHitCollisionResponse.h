#ifndef DAMAGEHITCOLLISIONRESPONSE_H
#define DAMAGEHITCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class Faction;
class Damage;
class DamageHitResponse abstract : public CollisionResponse
{
	Damage* damage_component;
	Faction* faction_component;
public:
	DamageHitResponse(Damage* damage_component);
	DamageHitResponse();
	virtual ~DamageHitResponse();
	void attach_damage_component(Damage* damage_component) { this->damage_component = damage_component; }
	void attach_faction_component(Faction* faction_component) { this->faction_component = faction_component; }

	virtual bool response(GameObject* other, GameObject* my_owner);
};


#endif // !PROJECTILECOLLISIONRESPONSE_H

