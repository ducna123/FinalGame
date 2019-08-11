#pragma once
#pragma once
#pragma once
#include "Sprite2D.h"
#include "Application.h"


class  Pipe : public Sprite2D
{
public:
	Pipe(std::shared_ptr<Models>& model, std::shared_ptr<Shaders>& shader, std::shared_ptr<Texture>& texture);
	~Pipe();


	void		Update(GLfloat deltatime) override;

	bool		IsActive();
	void		SetActive(bool status);

	void		SetColliderSize(float sizeX, float sizeY);
	float		GetColliderSizeX();
	float		GetColliderSizeY();

	void		SetPosY(int pos);

	void		Updown();
	void		SetMoveY(bool status);
	bool		GetMoveY();

	int		    GetPosY();
	bool		checkColider = true;

private:
	bool	m_active;
	bool	m_moveY;
	float	m_SizeColliderX;
	float	m_SizeColliderY;
	float   m_PosY;
	float   m_speed;
};
