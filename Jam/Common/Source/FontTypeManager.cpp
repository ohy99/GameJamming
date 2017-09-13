#include "FontTypeManager.h"

#include "MeshList.h"
#include "LoadTextData.h"

FontType & FontTypeManager::get_font(FONT_TYPE type)
{
	return font_list[type];
}

FontTypeManager::FontTypeManager()
{
	font_list[CALIBRI].text_mesh = MeshList::GetInstance()->getMesh("CALIBRI");
	font_list[CALIBRI].textWidth = LoadTextData("Image//Calibri Data.csv");

	font_list[CHILLER].text_mesh = MeshList::GetInstance()->getMesh("CHILLER");
	font_list[CHILLER].textWidth = LoadTextData("Image//Chiller Data.csv");
}

FontTypeManager::~FontTypeManager()
{
}
