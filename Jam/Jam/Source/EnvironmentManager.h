#ifndef ENVIRONMENTMANAGER_H
#define ENVIRONMENTMANAGER_H

#include "SingletonTemplate.h"
#include <vector>
class GenericDecoration;
class EnvironmentManager : public Singleton<EnvironmentManager>
{
	friend Singleton;

	GenericDecoration* background;
	std::vector<GenericDecoration*> decorations;
public:
	void attach_background(GenericDecoration* background);
	void render_environment();
	void add_decorations(GenericDecoration* deco);

	GenericDecoration* get_background();
protected:
	EnvironmentManager();
	~EnvironmentManager();
};

#endif // !ENVIRONMENTMANAGER_H
