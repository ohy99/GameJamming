#ifndef  SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include <vector>

//this runs the template
struct Animation
{
	Animation() {}
	void Set(int _startFrame, int _endFrame, int _repeat, float _time, bool _active)
	{
		this->startFrame = _startFrame;
		this->endFrame = _endFrame;
		this->repeatCount = _repeat;
		this->animTime = _time;
		this->animTime = _active;

		this-> m_currentTime = 0.0f;
		this->m_currentFrame = 0;
	}

	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;//time to make one loop
	bool ended;//flag to say ended
	bool animActive;

	float m_currentTime;
	int m_currentFrame;

	void Update(double dt)
	{
		if (this == NULL)
			return;
		//If animation is active
		if (this->animActive == false)
			return;
		//Working
		this->m_currentTime += static_cast<float>(dt);
		int numFrame = Math::Max(1, this->endFrame - this->startFrame + 1);

		float frameTime = this->animTime / numFrame;

		this->m_currentFrame = Math::Min(this->endFrame, this->startFrame +
			static_cast<int>(this->m_currentTime / frameTime));

		if (this->m_currentTime >= this->animTime)
		{
			if (this->repeatCount == 0)
			{
				this->animActive = false;
				this->m_currentTime = 0.0f;
				this->m_currentFrame = this->startFrame;
				this->ended = true;
			}

			if (this->repeatCount >= 1)
			{
				this->m_currentTime = 0.0f;
				this->m_currentFrame = this->startFrame;

			}
		}
	}
};

//THis works as the template for sprite animation
class SpriteAnimation : public Mesh
{
public:
	SpriteAnimation(const std::string &meshName, int row, int col);
	//SpriteAnimation(){}
	~SpriteAnimation();
	void Update(double dt);
	virtual void Render();

	int m_row;
	int m_col;

	Animation *m_anim;
};




#endif