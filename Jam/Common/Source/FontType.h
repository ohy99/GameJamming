#pragma once

#ifndef _FONTTYPE_H
#define _FONTTYPE_H


#include "MeshList.h"
class Mesh;

class FontType
{
public:
	virtual ~FontType() {
		if (textWidth != nullptr)
			delete textWidth;
		textWidth = nullptr;
	}
	float* textWidth;
	Mesh* text_mesh;

	Mesh* getMesh()
	{
		return text_mesh;
	}

	FontType() {
		textWidth = nullptr;
		text_mesh = MeshList::GetInstance()->getMesh("CALIBRI");
	}

};

#endif
