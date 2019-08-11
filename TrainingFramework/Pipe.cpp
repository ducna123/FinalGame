#include "Pipe.h"

Pipe::Pipe(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_moveY = false;
	m_speed = 100.0;
	m_active = true;
}

Pipe::~Pipe()
{
}


int timeUp = 1500;
int timeDown = 0;

void Pipe::Update(GLfloat deltatime)
{
	if (!m_active)
		return;
	Vector2 pos = Get2DPosition();
	pos.x = pos.x - m_speed * deltatime;

	if (m_moveY)
	{
		if (timeUp > 0)
		{
			timeUp--;
			pos.y = pos.y - 40 * deltatime;
			//std::cout << timeDown << std::endl;

		}
		else
		{
			timeDown++;
			//std::cout << timeDown << std::endl;

			pos.y = pos.y + 40 * deltatime;
			if (timeDown == 1500) {
				timeUp = 1500;
				timeDown = 0;
			}
		}
	}

	Set2DPosition(pos);

	if (pos.x <= -40 || pos.x > 800) {
		m_active = false;
		m_moveY = false;
	}

	if (pos.x < 250) checkColider = false;
}

void Pipe::SetMoveY(bool status)
{
	m_moveY = status;
}

bool Pipe::GetMoveY()
{
	return m_moveY;
}

bool Pipe::IsActive()
{
	return m_active;
}

void Pipe::SetActive(bool status)
{
	m_active = status;
}

void Pipe::SetColliderSize(float sizeX, float sizeY)
{
	m_SizeColliderX = sizeX;
	m_SizeColliderY = sizeY;
}
float Pipe::GetColliderSizeX()
{
	return m_SizeColliderX;
}
float Pipe::GetColliderSizeY()
{
	return m_SizeColliderY;
}

void Pipe::SetPosY(int pos)
{
	m_PosY = pos;
}

int Pipe::GetPosY()
{
	return m_PosY;
}

void Pipe::Updown() 
{
	float posY = Get2DPosition().y;



}