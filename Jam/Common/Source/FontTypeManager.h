#ifndef FONTTYPEMANAGER_H
#define FONTTYPEMANAGER_H

#include "SingletonTemplate.h"
#include "FontType.h"
#include <map>

class FontTypeManager : public Singleton<FontTypeManager>
{
public:
	enum FONT_TYPE
	{
		CALIBRI,
		CHILLER, 
		FT_COUNT
	};
private:
	friend Singleton<FontTypeManager>;
	FontType font_list[FONT_TYPE::FT_COUNT];
public:
	FontType& get_font(FONT_TYPE type = FONT_TYPE::CALIBRI);
protected:
	FontTypeManager();
	~FontTypeManager();
};

#endif // !FontTypeManager_H
