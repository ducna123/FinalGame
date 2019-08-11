#include "Bird.h"
#include "Pipe.h"

Bird::Bird(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture)
	:Sprite2D(model, shader, texture)
{
	m_speed = 50;
	m_allive = true;
	m_SizeCollider = 50;
	m_point = 0;
}

Bird::~Bird()
{
}

void Bird::Update(GLfloat deltatime)
{
	if (!m_allive)
		return;
	Vector2 pos = Get2DPosition();
	pos.y = pos.y + m_speed * deltatime;
	Set2DPosition(pos);
}

int Bird::GetPoint()
{
	return m_point;
}

bool Bird::IsAlive()
{
	return m_allive;
}

void Bird::SetIsAlive(bool status)
{
	m_allive = status;
}

void Bird::SetColliderSize(float size)
{
	m_SizeCollider = size;
}
float Bird::GetColliderSize()
{
	return m_SizeCollider;
}

float Bird::Distance(float a, float b)
{
	return b - a;
}

void Bird::PlusPoint()
{
	m_point++;
}

void Bird::CheckColider(std::list<std::shared_ptr<Pipe>>& listPipeUp, std::list<std::shared_ptr<Pipe>>& listPipeDown)
{
	Vector2 pos = Get2DPosition();

	for (auto pipe : listPipeUp)
	{
		if (pipe->IsActive() && pipe->checkColider)
		{
			if (Distance(pos.x, pipe->Get2DPosition().x) < m_SizeCollider + pipe->GetColliderSizeX()
				&& Distance(pipe->Get2DPosition().y, pos.y) < m_SizeCollider + pipe->GetColliderSizeY())
			{
				pipe->SetActive(false);
				pipe->Set2DPosition(-30, pipe->Get2DPosition().y);
				SetIsAlive(false);
			}
		}
	}

	for (auto pipe : listPipeDown)
	{
		if (pipe->IsActive() && pipe->checkColider)
		{
			if (Distance(pos.x, pipe->Get2DPosition().x) < m_SizeCollider + pipe->GetColliderSizeX()
				&& Distance(pos.y, pipe->Get2DPosition().y) < m_SizeCollider + pipe->GetColliderSizeY())
			{
				pipe->SetActive(false);
				pipe->Set2DPosition(-30, pipe->Get2DPosition().y);
				SetIsAlive(false);
			}
		}
	}

	if(pos.y > 380) SetIsAlive(false);
	if(pos.y < -10) SetIsAlive(false);

}

void Bird::SetPosY(int pos)
{
	m_PosY = pos;
}

int Bird::GetPosY()
{
	return m_PosY;
}

void Bird::Fly(float jump)
{
	Vector2 pos = Get2DPosition();
	pos.y = pos.y - m_speed * jump;
	Set2DPosition(pos);
}

void Bird::Dead()
{
	Vector2 pos = Get2DPosition();

	if (pos.y < 375)
	{
		pos.y = pos.y + m_speed * 0.03;
		Set2DPosition(pos);
	}
	
}