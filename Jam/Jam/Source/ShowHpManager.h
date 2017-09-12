#ifndef SHOWHPMANAGER_H
#define SHOWHPMANAGER_H

#include "SingletonTemplate.h"

#include <list>
#include "Vector3.h"
#include "FontType.h"
#include "Vertex.h"

class ShowHpManager : public Singleton<ShowHpManager>
{
	friend Singleton;
	struct HPTEXT
	{
		int value;
		double elapsed_time;
		const double active_duration;
		Vector3 pos;
		Vector3 scale;
		Vector3 dir;
		Color color;
		HPTEXT(Vector3 pos, int value = 0, double duration = 0.0);
		void render(FontType* font);
	};
	std::list< HPTEXT* > hp_text;
	Vector3 default_scale;
	double default_duration;
	float default_speed;
	float default_scaling_speed;
	Vector3 default_disappearing_direction;
	FontType chiller_font;

	FontType calibri;
public:
	void update(double dt);
	void render_all_hp_text();
	void generate_hp_text(Vector3 pos, int value = 0, bool is_crit = false);//in case doing crit can just enable tat
	FontType& get_font();

	FontType& get_calibri();
protected:
	ShowHpManager();
	~ShowHpManager();
};


#endif // !SHOWHPMANAGER_H
