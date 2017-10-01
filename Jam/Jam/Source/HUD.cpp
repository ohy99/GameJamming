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
	FontType& font = FontTypeManager::GetInstance()->get_font(FontTypeManager::CALIBRI);
	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	Vector3 text_scale(5, 5, 1);

	float half_width = 0.f;
	std::string textstr = "Score : " + std::to_string(Player::GetInstance()->get_point());
	for (unsigned int i = 0; i < textstr.size(); ++i)
		half_width += font.textWidth[(int)textstr.at(i)];

	half_width *= 0.5f;

	MS& ms = Graphics::GetInstance()->modelStack;

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

	ms.Translate(-half_width, -2, 0);
	ms.Scale(4, 4, 1);
	RenderHelper::RenderText(&font, ss.str(), Color(0.5f, 0.5f, 0.5f));
	ms.PopMatrix();

	
}
