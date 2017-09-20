#ifndef CROWDCONTROL_H
#define CROWDCONTROL_H

//***************************************************
//
//	Here houses all possible Cc in game
//
//***************************************************
class CrowdControl abstract
{
public:
	enum CC
	{
		NONE = 0,
		SLOW,
		STUN,
		KNOCKBACK
	} crowdControl;
	CrowdControl() { crowdControl = (CC)0; }
	virtual ~CrowdControl(){}
};

#endif // !CROWNDCONTROL_H
