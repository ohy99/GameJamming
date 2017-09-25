#include "HUD.h"

#include "Graphics.h"
#include "RenderHelper.h"
#include "FontTypeManager.h"
#include "GlobalVariableManager.h"
#include "Player.h"

HUD::HUD()
{
}

HUD::~HUD()
{
}

void HUD::render()
{
	FontType& font = FontTypeManager::GetInstance()->get_font(FontTypeManager::CALIBRI);
	float worldWidth = GlobalVariables::GetInstance()->get_worldWidth();
	float worldHeight = GlobalVariables::GetInstance()->get_worldHeight();
	Vector3 text_scale(5, 5, 1);

	float half_width = 0.f;
	std::string textstr = "Score : " + std::to_string(Player::GetInstance()->get_point());
	for (int i = 0; i < textstr.size(); ++i)
		half_width += font.textWidth[(int)textstr.at(i)];

	half_width *= 0.5f;

	MS& ms = Graphics::GetInstance()->modelStack;

	ms.PushMatrix();
	ms.Translate(worldWidth * 0.5f, worldHeight * 0.95f, 0);
	ms.Scale(text_scale);
	ms.Translate(-half_width, 0 ,0);
	RenderHelper::RenderText(&font, textstr, Color(0, 1, 0));
	ms.PopMatrix();
}
