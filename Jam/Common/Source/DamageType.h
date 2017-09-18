#ifndef DAMAGETYPE_H
#define DAMAGETYPE_H

//****************************************
//
//	Holds the value of damage. aka carrier
//
//*****************************************
class DamageType
{
public:
	//this let us know what this dmg collider is.
	//possible use is something like increase melee dmg taken etc
	//can even add elements like fire/ice
	enum DMG_TYPE
	{
		ENVIRONMENT,
		PROJECTILE,
		MELEE
	};

protected:
	DMG_TYPE type;
	DamageType() {}
public:
	~DamageType() {}
	void set_type(DMG_TYPE type = DMG_TYPE::ENVIRONMENT) { this->type = type; }
	DMG_TYPE get_type() { return type; }
};

#endif // !DAMAGECOMPONENT_H
