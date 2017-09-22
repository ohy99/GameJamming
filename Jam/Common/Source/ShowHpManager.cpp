#include "ShowHpManager.h"

#include "MeshList.h"
#include "LoadTextData.h"

#include "Graphics.h"
#include "RenderHelper.h"
#include "FontTypeManager.h"

ShowHpManager::ShowHpManager() : chiller_font(FontTypeManager::GetInstance()->get_font(FontTypeManager::CHILLER)),
default_scale(4, 4, 0), default_duration(1.f),
default_speed(8.f), default_scaling_speed(2.f), default_disappearing_direction(0, 1, 0)
{
}

ShowHpManager::~ShowHpManager()
{
	this->clear_hptext();
}

void ShowHpManager::update(double dt)
{
	for (std::list<HPTEXT*>::iterator text_iter = hp_text.begin(); text_iter != hp_text.end();)
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

void ShowHpManager::clear_hptext()
{
	for each (auto &t in hp_text)
		delete t;
	
	hp_text.clear();
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

	//i wan centralize da text
	float half_width = 0.f;
	std::string textstr = std::to_string(this->value);
	for (int i = 0; i < textstr.size(); ++i)
		half_width += font->textWidth[(int)textstr.at(i)];
	
	half_width *= 0.5f;

	ms.PushMatrix();
	ms.Translate(this->pos);
	ms.Scale(this->scale);
	ms.Translate(-half_width);
	if (this->value < 0)
		this->value = -this->value;
	RenderHelper::RenderText(font, std::to_string(this->value), this->color);
	ms.PopMatrix();
}
