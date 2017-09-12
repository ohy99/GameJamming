#include "RenderHelper.h"
#include "Mesh.h"
#include "MatrixStack.h"

#include "Graphics.h"

#include "GL\glew.h"

#include "FontType.h"

void RenderHelper::RenderText(FontType* mesh, std::string text, Color color)
{
	if (!mesh || mesh->getMesh()->textureID <= 0)
		return;

	Graphics* g = Graphics::GetInstance();

	//glDisable(GL_DEPTH_TEST);
	glUniform1i(g->m_parameters[Graphics::U_TEXT_ENABLED], 1);
	glUniform3fv(g->m_parameters[Graphics::U_TEXT_COLOR], 1, &color.r);
	glUniform1i(g->m_parameters[Graphics::U_LIGHTENABLED], 0);
	glUniform1i(g->m_parameters[Graphics::U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->getMesh()->textureID);
	glUniform1i(g->m_parameters[Graphics::U_COLOR_TEXTURE], 0);
	float nextCharWidth = 0.0f;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		char Character = text[i];
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(nextCharWidth + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		nextCharWidth += (mesh->textWidth[Character]);
		Mtx44 MVP = g->projectionStack.Top() * g->viewStack.Top() * g->modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(g->m_parameters[Graphics::U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->getMesh()->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(g->m_parameters[Graphics::U_TEXT_ENABLED], 0);
	//glEnable(GL_DEPTH_TEST);
}

void RenderHelper::RenderTextOnScreen(FontType* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->getMesh()->textureID <= 0)
		return;


	Graphics* g = Graphics::GetInstance();
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	g->projectionStack.PushMatrix();
	g->projectionStack.LoadMatrix(ortho);
	g->viewStack.PushMatrix();
	g->viewStack.LoadIdentity();
	g->modelStack.PushMatrix();
	g->modelStack.LoadIdentity();
	g->modelStack.Translate(x, y, 0);
	g->modelStack.Scale(size, size, size);
	glUniform1i(g->m_parameters[Graphics::U_TEXT_ENABLED], 1);
	glUniform3fv(g->m_parameters[Graphics::U_TEXT_COLOR], 1, &color.r);
	glUniform1i(g->m_parameters[Graphics::U_LIGHTENABLED], 0);
	glUniform1i(g->m_parameters[Graphics::U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->getMesh()->textureID);
	glUniform1i(g->m_parameters[Graphics::U_COLOR_TEXTURE], 0);
	float nextCharWidth = 0.0f;
	for (unsigned i = 0; i < text.length(); ++i)
	{
		char Character = text[i];
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(nextCharWidth + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		nextCharWidth += (mesh->textWidth[Character]);
		Mtx44 MVP = g->projectionStack.Top() * g->viewStack.Top() * g->modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(g->m_parameters[Graphics::U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->getMesh()->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(g->m_parameters[Graphics::U_TEXT_ENABLED], 0);
	g->modelStack.PopMatrix();
	g->viewStack.PopMatrix();
	g->projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void RenderHelper::RenderMesh(Mesh *mesh, bool enableLight)
{
	if (mesh == nullptr)
		return;
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	Graphics* g = Graphics::GetInstance();

	MVP = g->projectionStack.Top() * g->viewStack.Top() * g->modelStack.Top();
	glUniformMatrix4fv(g->m_parameters[Graphics::U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && g->bLightEnabled)
	{
		glUniform1i(g->m_parameters[Graphics::U_LIGHTENABLED], 1);
		modelView = g->viewStack.Top() * g->modelStack.Top();
		glUniformMatrix4fv(g->m_parameters[Graphics::U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(g->m_parameters[Graphics::U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

		//load material
		glUniform3fv(g->m_parameters[Graphics::U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(g->m_parameters[Graphics::U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(g->m_parameters[Graphics::U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(g->m_parameters[Graphics::U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(g->m_parameters[Graphics::U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0)
	{
		glUniform1i(g->m_parameters[Graphics::U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(g->m_parameters[Graphics::U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(g->m_parameters[Graphics::U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
