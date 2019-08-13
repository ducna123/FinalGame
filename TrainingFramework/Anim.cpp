#include "Anim.h"


int time1 = 100;

Anim::Anim(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture, Vector2& pictureSize, Vector2& spriteSize, int start, int end, float lengthTime)
	:SpriteSheet(model, shader, texture, pictureSize, spriteSize, start, end, lengthTime)
{
	time1 = 100;
	m_active = true;
}

Anim::~Anim()
{
}

void Anim::Update(GLfloat deltatime)
{
	if (!m_active)
		return;

	SpriteSheet::Update(deltatime);
	if (SpriteSheet::IsDone())
	{
		if (time1 > 0)
		{
			time1--;
		}
		else m_active = false;
	}
}

bool Anim::IsActive()
{
	return m_active;
}

void Anim::SetActive(bool status)
{
	m_active = status;
	if (m_active)
	{
		time1 = 100;
		SpriteSheet::StartAnimation();
	}
}

