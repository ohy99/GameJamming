#include "Boss.h"

bool CheckDuplicate(BasePart* part, std::map<std::string, BasePart*> map){
	if (!map.empty()) {
		auto check = map.find(part->name);
		if (check != map.end())
			return true;
	}
	return false;
}

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::update(double dt)
{
	if (leftPart->active)
		leftPart->update(dt);
	if (middlePart->active)
		middlePart->update(dt);
	if (rightPart->active)
		rightPart->update(dt);
}

bool Boss::RegisterPart(BasePart* part, SIDE side)
{
	switch (side) {
	case 1:
		if (!CheckDuplicate(part, leftParts)) {
			leftParts[part->name] = part;
			return true;
		}
		break;
	case 2:
		if (!CheckDuplicate(part, middleParts)) {
			middleParts[part->name] = part;
			return true;
		}
		break;
	case 3:
		if (!CheckDuplicate(part, rightParts)) {
			rightParts[part->name] = part;
			return true;
		}
		break;
	}
	return false;
}
