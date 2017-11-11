#include "HUD.h"

#include "Graphics.h"
#include "RenderHelper.h"
#include "FontTypeManager.h"
#include "GlobalVariableManager.h"
#include "Player.h"
#include "MeshBuilder.h"
#include "MyDebugger.h"
#include <sstream>

HUD::HUD() : num_of_combo_circles(20), start_angle(0), end_angle(360), circle_color(0.5f,0.6f,1.0f)
{
	combo_circle = new Mesh*[num_of_combo_circles];
	float total_angle = end_angle - start_angle;
	combo_circle[0] = nullptr;
	for (int i = 1; i < num_of_combo_circles; ++i)
	{
		combo_circle[i] = MeshBuilder::GenerateCircle("part" + std::to_string(i), circle_color, 20,
			((float)(i + 1) / (float)num_of_combo_circles) * total_angle);
	}
	combo = MeshBuilder::GenerateCircle("", Color(1, 1, 1), 20);

	frontBackHp.first = MeshList::GetInstance()->getMesh("HpFront");
	frontBackHp.second = MeshList::GetInstance()->getMesh("HpBack");
}

HUD::~HUD()
{
	for (int i = 0; i < num_of_combo_circles; ++i)
	{
		delete combo_circle[i];
	}
	delete combo_circle;

	delete combo;
}

void HUD::render()
{
	MS& ms = Graphics::GetInstance()->modelStack;
	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	//Render HP
	ms.PushMatrix();
	ms.Translate(20, 90, 0);
	
	ms.PushMatrix();
	ms.Scale(30, 10, 1);
	RenderHelper::RenderMesh(frontBackHp.second, false);
	ms.PopMatrix();

	ms.PushMatrix();
	ms.Scale(18.f * Player::GetInstance()->hitpoint.get_hp_percentage(), 4.5f, 1);
//	ms.Translate((1.0f - Player::GetInstance()->hitpoint.get_hp_percentage()) * -1.f, 0.f, 0.0f);
	ms.Translate(0.25f/* + (1.0f - Player::GetInstance()->hitpoint.get_hp_percentage()) * -0.5f*/, -0.275, 0.0f);
	//ms.Translate(0.25f + (1.0f - Player::GetInstance()->hitpoint.get_hp_percentage()) * -0.5f, -0.275, 0.0f);
	RenderHelper::RenderMesh(frontBackHp.first, false);
	ms.PopMatrix();

	ms.PopMatrix();


	FontType& font = FontTypeManager::GetInstance()->get_font(FontTypeManager::CALIBRI);
	Vector3 text_scale(5, 5, 1);

	float half_width = 0.f;
	std::string textstr = "Score : " + std::to_string(Player::GetInstance()->get_point());
	for (unsigned int i = 0; i < textstr.size(); ++i)
		half_width += font.textWidth[(int)textstr.at(i)];

	half_width *= 0.5f;

	

	ms.PushMatrix();
	ms.Translate(worldWidth * 0.5f, worldHeight * 0.95f, 0);
	ms.Scale(text_scale);
	ms.Translate(-half_width, 0 ,0);
	RenderHelper::RenderText(&font, textstr, Color(0, 1, 0));
	ms.PopMatrix();


	ms.PushMatrix();
	ms.Translate(worldWidth * 0.7f, worldHeight * 0.95f, 0);

	ms.PushMatrix();
	ms.Rotate(90.f, 1, 0, 0);

	ms.PushMatrix();
	ms.Rotate(90.f, 0, 1, 0);
	ms.Scale(3, 1, 3);
	RenderHelper::RenderMesh(combo_circle[unsigned((1.f - Player::GetInstance()->get_combo_timer().get_current_percent()) * (num_of_combo_circles - 1))], false);
	//RenderHelper::RenderMesh(combo_circle[part], false);
	ms.PopMatrix();

	ms.Scale(2, 1, 2);
	RenderHelper::RenderMesh(combo, false);
	ms.PopMatrix();

	half_width = 0.f;
	std::stringstream ss;
	ss << std::fixed;
	ss.precision(1);
	ss << Player::GetInstance()->get_multiplier() << "X";
	textstr = ss.str();
	for (unsigned int i = 0; i < textstr.size(); ++i)
		half_width += font.textWidth[(int)textstr.at(i)];
	half_width *= 0.5f;

	ms.Scale(3, 3, 1);
	ms.Translate(-half_width, -0.5, 0);
	RenderHelper::RenderText(&font, ss.str(), Color(0.5f, 0.5f, 0.5f));
	ms.PopMatrix();

	
	//second wind thing
	if (Player::GetInstance()->second_wind_active)
	{
		if (!Player::GetInstance()->GetDead()) {
			ss.str("");
			half_width = 0.f;
			ss << "Second Wind!";
			textstr = ss.str();
			for (unsigned int i = 0; i < textstr.size(); ++i)
				half_width += font.textWidth[(int)textstr.at(i)];
			half_width *= 0.5f;

			ms.PushMatrix();
			ms.Translate(worldWidth * 0.5f, worldHeight * 0.6f, 0);
			ms.Scale(10, 10, 1);
			ms.Translate(-half_width, -0.5, 0);
			RenderHelper::RenderText(&font, ss.str(), Color(0.8f, 0.2f, 0.2f, 0.6f));
			ms.PopMatrix();

			ss.str("");
			half_width = 0.f;
			ss.precision(2);
			ss << (Player::GetInstance()->second_wind_timer.get_duration() - Player::GetInstance()->second_wind_timer.get_elapsed_time());
			textstr = ss.str();
			for (unsigned int i = 0; i < textstr.size(); ++i)
				half_width += font.textWidth[(int)textstr.at(i)];
			half_width *= 0.5f;

			ms.PushMatrix();
			ms.Translate(worldWidth * 0.5f, worldHeight * 0.5f, 0);
			ms.Scale(15, 15, 1);
			ms.Translate(-half_width, -0.5, 0);
			RenderHelper::RenderText(&font, ss.str(), Color(0.8f, 0.2f, 0.2f, 0.8f));
			ms.PopMatrix();
		}
	}

	if (Player::GetInstance()->GetDead()) {
		/*ss.str("");
		ss << "Press Enter to return to main menu";
		ms.Scale(3, 3, 1);
		ms.Translate(-, -0.5, 0);
		RenderHelper::RenderText(&font, ss.str(), Color(0.5f, 0.5f, 0.5f));
		ms.PopMatrix();*/
	}
}
