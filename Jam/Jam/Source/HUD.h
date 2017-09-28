#ifndef HUD_H
#define HUD_H

#include "SingletonTemplate.h"
#include "Vertex.h"
class Mesh;
class HUD : public Singleton <HUD>
{
	friend Singleton;

	Mesh** combo_circle;
	Mesh* combo;
	unsigned num_of_combo_circles;
	float start_angle;
	float end_angle;
	Color circle_color;


public:
	void render();
protected:
	HUD();
	~HUD();
};

#endif // !HUD_H

