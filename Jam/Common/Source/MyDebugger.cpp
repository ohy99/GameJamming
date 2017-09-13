#include "MyDebugger.h"

#include "Graphics.h"
#include "RenderHelper.h"
#include "FontTypeManager.h"

void MyDebugger::render_debug_info()
{
	MS& ms = Graphics::GetInstance()->modelStack;
	FontType* font = &FontTypeManager::GetInstance()->get_font();

	int num = 0;
	for each (const auto &p in debug_info)
	{
		ms.PushMatrix();
		ms.Translate(0, num++ * text_scale.y, 0);
		ms.Scale(text_scale);
		RenderHelper::RenderText(font, p.second.str(), Color(0, 1, 0));
		ms.PopMatrix();
	}

	debug_info.clear();
}

MyDebugger::MyDebugger() : text_scale(3,3,0)
{
}

MyDebugger::~MyDebugger()
{
}
