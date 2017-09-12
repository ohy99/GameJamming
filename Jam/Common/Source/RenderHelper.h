#ifndef RENDER_HELPER_H
#define RENDER_HELPER_H



#include "Vertex.h"
#include "Mesh.h"
class FontType;

class RenderHelper
{
public:
	static void RenderMesh(Mesh* _mesh, bool enableLight);
	//static void RenderMeshWithLight(Mesh* _mesh);
	static void RenderText(FontType* mesh, std::string text, Color color);
	static void RenderTextOnScreen(FontType* mesh, std::string text, Color color, float size, float x, float y);

	//static void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y);
};

#endif // RENDER_HELPER_H