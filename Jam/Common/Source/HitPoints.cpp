#include "HitPoints.h"

#include "MyMath.h"
#include <iostream>
#include "HpBar.h"
#include "ShowHpManager.h"

HitPoint::HitPoint() : max_hitpoint(1), hitpoint(1)
{
}

HitPoint::~HitPoint()
{
}

void HitPoint::init_hp(int max_hp)
{
	this->hitpoint = this->max_hitpoint = max_hp;
}

void HitPoint::set_maxhp(int max_hp)
{
	this->max_hitpoint = max_hp;
}

int HitPoint::get_maxhp()
{
	return this->max_hitpoint;
}

float HitPoint::get_hp_percentage()
{
	return (float)this->hitpoint / (float)this->max_hitpoint;
}

int HitPoint::get_hp()
{
	return this->hitpoint;
}

int HitPoint::kena_hit(int damage, Vector3* pos, bool is_crit)
{
	if (damage < 0)
	{
		std::cout << "Negative damage : " << damage << ". Are you sure this is intended?/n"
			<< "(Info) " << this << " Hp = " << this->hitpoint << " , MaxHp = " << this->max_hitpoint << std::endl;
		damage = 0;
	}
	int diff = this->hitpoint;
	this->hitpoint = Math::Max(this->hitpoint - damage, 0);
	diff -= this->hitpoint;

	if (pos)
		ShowHpManager::GetInstance()->generate_hp_text(*pos, diff, false);

	return this->hitpoint;
}

int HitPoint::kena_hit_currenthp(float percent_of_current_hp, Vector3* pos, bool is_crit)
{
	if (percent_of_current_hp < 0.f)
	{
		std::cout << "Negative percentage-currhp damage : " << percent_of_current_hp << ". Are you sure this is intended?/n"
			<< "(Info) " << this << " Hp = " << this->hitpoint << " , MaxHp = " << this->max_hitpoint << std::endl;
		percent_of_current_hp = 0.f;
	}
	int diff = this->hitpoint;
	this->hitpoint = Math::Max(this->hitpoint - (int)(percent_of_current_hp * this->hitpoint), 0);
	diff -= this->hitpoint;

	if (pos)
		ShowHpManager::GetInstance()->generate_hp_text(*pos, diff, false);

	return this->hitpoint;
}

int HitPoint::kena_hit_maxhp(float percent_of_max_hp, Vector3* pos, bool is_crit)
{
	if (percent_of_max_hp < 0.f)
	{
		std::cout << "Negative percentage-maxhp damage : " << percent_of_max_hp << ". Are you sure this is intended?/n"
			<< "(Info) " << this << " Hp = " << this->hitpoint << " , MaxHp = " << this->max_hitpoint << std::endl;
		percent_of_max_hp = 0.f;
	}
	int diff = this->hitpoint;
	this->hitpoint = Math::Max(this->hitpoint - (int)(percent_of_max_hp * this->max_hitpoint), 0);
	diff -= this->hitpoint;

	if (pos)
		ShowHpManager::GetInstance()->generate_hp_text(*pos, diff, false);

	return this->hitpoint;
}

int HitPoint::kena_heal(int heal, Vector3* pos, bool is_crit)
{
	if (heal < 0)
	{
		std::cout << "Negative healing : " << heal << ". Are you sure this is intended?/n"
			<< "(Info) " << this << " Hp = " << this->hitpoint << " , MaxHp = " << this->max_hitpoint << std::endl;
		heal = 0;
	}
	int diff = this->hitpoint;
	this->hitpoint = Math::Min(this->hitpoint + heal, this->max_hitpoint);
	diff -= this->hitpoint;

	if (pos)
		ShowHpManager::GetInstance()->generate_hp_text(*pos, diff, false);

	return this->hitpoint;
}

int HitPoint::kena_heal_currenthp(float percent_of_current_hp, Vector3* pos, bool is_crit)
{
	if (percent_of_current_hp < 0.f)
	{
		std::cout << "Negative percentage-currhp healing : " << percent_of_current_hp << ". Are you sure this is intended?/n"
			<< "(Info) " << this << " Hp = " << this->hitpoint << " , MaxHp = " << this->max_hitpoint << std::endl;
		percent_of_current_hp = 0.f;
	}
	int diff = this->hitpoint;
	this->hitpoint = Math::Min(this->hitpoint + (int)(percent_of_current_hp * this->hitpoint), this->max_hitpoint);
	diff -= this->hitpoint;

	if (pos)
		ShowHpManager::GetInstance()->generate_hp_text(*pos, diff, false);

	return this->hitpoint;
}

int HitPoint::kena_heal_maxhp(float percent_of_max_hp, Vector3* pos, bool is_crit)
{
	if (percent_of_max_hp < 0.f)
	{
		std::cout << "Negative percentage-maxhp healing : " << percent_of_max_hp << ". Are you sure this is intended?/n"
			<< "(Info) " << this << " Hp = " << this->hitpoint << " , MaxHp = " << this->max_hitpoint << std::endl;
		percent_of_max_hp = 0.f;
	}
	int diff = this->hitpoint;
	this->hitpoint = Math::Min(this->hitpoint + (int)(percent_of_max_hp * this->max_hitpoint), this->max_hitpoint);
	diff -= this->hitpoint;

	if (pos)
		ShowHpManager::GetInstance()->generate_hp_text(*pos, diff, false);

	return this->hitpoint;
}

void HitPoint::render_hpbar(Vector3 pos, Vector3 scale, std::string foreground_mesh, std::string background_mesh)
{
	if (foreground_mesh != "")
		HpBar::GetInstance()->greenBar = MeshList::GetInstance()->getMesh(foreground_mesh);
	if (background_mesh != "")
		HpBar::GetInstance()->redBar = MeshList::GetInstance()->getMesh(background_mesh);

	HpBar::GetInstance()->pos = pos;
	HpBar::GetInstance()->scale = scale;

	HpBar::GetInstance()->render(this->get_hp_percentage());

	HpBar::GetInstance()->reset_default_mesh();
}
