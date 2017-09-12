#include "SpriteAnimation.h"
#include "GL\glew.h"
#include "Vertex.h"


SpriteAnimation::SpriteAnimation(const std::string &meshName, int row, int col) : Mesh(meshName),
m_row(row),
m_col(col),

m_anim(NULL)
{
}

SpriteAnimation::~SpriteAnimation()
{
	//if (m_anim)
	//{
	//	delete m_anim;
	//	m_anim = NULL;
	//}
}

void SpriteAnimation::Update(double dt)
{
	//Data check
	if (m_anim == NULL)
		return;
	//If animation is active
	if (m_anim->animActive == false)
		return;
	//Working
	m_anim->m_currentTime += static_cast<float>(dt);
	int numFrame = Math::Max(1, m_anim->endFrame - m_anim->startFrame + 1);

	float frameTime = m_anim->animTime / numFrame;

	m_anim->m_currentFrame = Math::Min(m_anim->endFrame, m_anim->startFrame + 
		static_cast<int>(m_anim->m_currentTime / frameTime));

	if (m_anim->m_currentTime >= m_anim->animTime)
	{
		if (m_anim->repeatCount == 0)
		{
			m_anim->animActive = false;
			m_anim->m_currentTime = 0.0f;
			m_anim->m_currentFrame = m_anim->startFrame;
			m_anim->ended = true;
		}

		if (m_anim->repeatCount >= 1)
		{
			m_anim->m_currentTime = 0.0f;
			m_anim->m_currentFrame = m_anim->startFrame;
			
		}
	}
	//std::cout << m_currentTime << std::endl;
}

void SpriteAnimation::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));


	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));


	//glDrawArrays(GL_TRIANGLES, offset, count);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	indexSize = 6;
	if (m_anim)
	{
		if (mode == DRAW_LINES)
			glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, (void*)(m_anim->m_currentFrame * 6 * sizeof(GLuint)));
		else if (mode == DRAW_TRIANGLE_STRIP)
			glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, (void*)(m_anim->m_currentFrame * 6 * sizeof(GLuint)));
		else
			glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, (void*)(m_anim->m_currentFrame * 6 * sizeof(GLuint)));
	}
	else
	{
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, (void*)(0 * 6 * sizeof(GLuint)));
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);






}