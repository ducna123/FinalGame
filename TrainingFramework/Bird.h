#pragma once
#pragma once

#include "Sprite2D.h"
#include "Application.h"
#include "Pipe.h"

class  Bird : public Sprite2D
{
public:
	Bird(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Bird();


	void		Update(GLfloat deltatime) override;
	void        Fly(float jump);

	float		Distance(float a, float b);

	bool		IsAlive();
	void		SetIsAlive(bool status);

	void		SetColliderSize(float size);
	float		GetColliderSize();

	void		SetPosY(int pos);
	int		    GetPosY();
	void		Dead();

	void		CheckColider(std::list<std::shared_ptr<Pipe>>& m_listPipeUp, std::list<std::shared_ptr<Pipe>>& m_listPipeDown);
	void		PlusPoint();
	int			GetPoint();


private:
	bool	m_allive;
	float	m_SizeCollider;
	float   m_PosY;
	float   m_speed;

	int		m_point;
};