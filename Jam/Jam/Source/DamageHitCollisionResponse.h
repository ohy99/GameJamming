#ifndef DAMAGEHITCOLLISIONRESPONSE_H
#define DAMAGEHITCOLLISIONRESPONSE_H

#include "CollisionResponse.h"

class Faction;
class Damage;
class DamageHitResponse : public CollisionResponse
{
	Damage* damage_component;
	Faction* faction_component;
public:
	DamageHitResponse(Damage* damage_component);
	DamageHitResponse();
	~DamageHitResponse();
	void attach_damage_component(Damage* damage_component) { this->damage_component = damage_component; }
	void attach_faction_component(Faction* faction_component) { this->faction_component = faction_component; }

	virtual void response(GameObject* other);
};


#endif // !PROJECTILECOLLISIONRESPONSE_H

