#include "ShowHpManager.h"

#include "MeshList.h"
#include "LoadTextData.h"

#include "Graphics.h"
#include "RenderHelper.h"

ShowHpManager::ShowHpManager() : default_scale(3, 3, 0), default_duration(1.f),
	default_speed(4.f), default_scaling_speed(1.f), default_disappearing_direction(0, 1 ,0)
{
	chiller_font.text_mesh = MeshList::GetInstance()->getMesh("CHILLER");
	chiller_font.textWidth = LoadTextData("Image//Chiller Data.csv");

	calibri.text_mesh = MeshList::GetInstance()->getMesh("CALIBRI");
	calibri.textWidth = LoadTextData("Image//Calibri Data.csv");
}

ShowHpManager::~ShowHpManager()
{
}

void ShowHpManager::update(double dt)
{
	for (std::list<HPTEXT*>::iterator text_iter = hp_text.begin(); text_iter!= hp_text.end();)
	{
		HPTEXT* text = (*text_iter);
		if (text->elapsed_time < text->active_duration)
		{
			text->pos += default_disappearing_direction * default_speed * (float)dt;
			text->scale -= Vector3(default_scaling_speed, default_scaling_speed) * (float)dt;
			
			text->elapsed_time += dt;
			++text_iter;
		}
		else
		{
			text_iter = hp_text.erase(text_iter);
			delete text;
		}
	}
}

void ShowHpManager::render_all_hp_text()
{
	for each (auto &text in hp_text)
		text->render(&this->chiller_font);
}

void ShowHpManager::generate_hp_text(Vector3 pos, int value, bool is_crit)
{
	HPTEXT* temp = new HPTEXT(pos, value, default_duration);
	temp->scale = default_scale;
	if (value < 0)
		temp->color.Set(0, 1, 0);//healing is green color
	hp_text.push_back(temp);
}

FontType & ShowHpManager::get_font()
{
	return chiller_font;
}

FontType & ShowHpManager::get_calibri()
{
	// TODO: insert return statement here
	return this->calibri;
}


ShowHpManager::HPTEXT::HPTEXT(Vector3 pos, int value, double duration) :
	value(value), 
	elapsed_time(0.0),
	active_duration(duration),
	pos(pos),
	scale(1, 1, 1),
	dir(0, 1, 0),
	color(1, 0, 0)
{
}

void ShowHpManager::HPTEXT::render(FontType* font)
{
	MS& ms = Graphics::GetInstance()->modelStack;

	ms.PushMatrix();
	ms.Translate(this->pos);
	ms.Scale(this->scale);
	if (this->value < 0)
		this->value = -this->value;
	RenderHelper::RenderText(font, std::to_string(this->value), this->color);
	ms.PopMatrix();
}
