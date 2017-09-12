#include "EnvironmentManager.h"

//#include "GenericDecoration.h"

EnvironmentManager::EnvironmentManager()
{
}

EnvironmentManager::~EnvironmentManager()
{
}

void EnvironmentManager::attach_background(GenericDecoration * background)
{
	this->background = background;
}

void EnvironmentManager::add_decorations(GenericDecoration* deco)
{
	this->decorations.push_back(deco);
}

GenericDecoration * EnvironmentManager::get_background()
{
	return this->background;
}

void EnvironmentManager::render_environment()
{
	//always render background first
	//background->render();

	//for each (auto &d in decorations)
	//{
	//	if (d->active)
	//		d->render();
	//}
}
