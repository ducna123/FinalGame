#include "GSPlay1.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <time.h>
#include <sstream>
#include <iomanip>
#include <thread>


int screenWidth = 800; //need get on Graphic engine
int screenHeight = 480; //need get on Graphic engine

float timePlus;

GSPlay1::GSPlay1()
{
	m_SpawnCooldown = 2;
	timePlus = 10;
}


GSPlay1::~GSPlay1()
{

}


void GSPlay1::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BGDay");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Land
	texture = ResourceManagers::GetInstance()->GetTexture("land");
	m_Land = std::make_shared<Sprite2D>(model, shader, texture);
	m_Land->Set2DPosition(screenWidth / 2, screenHeight / 2 + 300);
	m_Land->SetSize(900, 285);

	//pipe
	/*texture = ResourceManagers::GetInstance()->GetTexture("pipeUp");
	m_Pipe1 = std::make_shared<Sprite2D>(model, shader, texture);
	m_Pipe1->Set2DPosition(screenWidth / 2, 0);
	m_Pipe1->SetSize(60, 300);

	texture = ResourceManagers::GetInstance()->GetTexture("pipeDown");
	m_Pipe2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_Pipe2->Set2DPosition(screenWidth / 2, 400);
	m_Pipe2->SetSize(60, 300);*/


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 0", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Bird");
	m_Bird = std::make_shared<Bird >(model, shader, texture);
	m_Bird->Set2DPosition(30, screenHeight / 2);
	m_Bird->SetSize(50, 37);
	m_Bird->SetColliderSize(20);

	//SoundManager::GetInstance()->AddSound("bground");
	//SoundManager::GetInstance()->PlaySound("bground");

}

void GSPlay1::Exit()
{

}


void GSPlay1::Pause()
{

}

void GSPlay1::Resume()
{

}


void GSPlay1::HandleEvents()
{

}

void GSPlay1::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlay1::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!bIsPressed)
		if (m_Bird->IsAlive())
			m_Bird->Fly(0.5);

}

void GSPlay1::Update(float deltaTime)
{
	if (m_Bird->IsAlive())
	{
		if (m_SpawnCooldown > 0)
		{
			m_SpawnCooldown -= deltaTime;
		}
		if (m_SpawnCooldown <= 0)
		{

			srand(time(0));
			int a = rand() % 40 + 1;

			CreatRandomPipeDown(a);
			CreatRandomPipeUp(a);
			m_SpawnCooldown = 3;
		}

		if (timePlus > 0) timePlus -= deltaTime;
		if (timePlus <= 0) {
			m_Bird->PlusPoint();
			std::stringstream stream;
			stream << std::fixed << std::setprecision(0) << m_Bird->GetPoint();
			std::string score = "score: " + stream.str();
			m_score->setText(score);
			timePlus = 3;
		}

		for (auto Pipe : m_listPipeUp)
		{
			if (Pipe->IsActive())
			{
				Pipe->Update(deltaTime);
			}
		}

		for (auto Pipe : m_listPipeDown)
		{
			if (Pipe->IsActive())
			{
				Pipe->Update(deltaTime);
			}
		}
	}

	if (m_Bird->IsAlive())
	{
		m_Bird->Update(deltaTime);
		m_Bird->CheckColider(m_listPipeUp, m_listPipeDown);
	}


}

void GSPlay1::Draw()
{


	m_BackGround->Draw();

	for (auto pipe : m_listPipeDown)
	{
		pipe->Draw();
	}

	for (auto pipe : m_listPipeUp)
	{
		pipe->Draw();
	}
	m_Bird->Draw();

	m_Land->Draw();
	m_score->Draw();
}

void GSPlay1::CreatRandomPipeUp(int x)
{
	Vector2 posUp;
	posUp.x = 800;
	posUp.y = 0 + x;


	for (auto pipe : m_listPipeUp)
	{
		if (!pipe->IsActive())
		{
			pipe->SetActive(true);
			pipe->Set2DPosition(posUp);
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("pipeUp");

	std::shared_ptr<Pipe> pipeUp = std::make_shared<Pipe>(model, shader, texture);
	pipeUp->Set2DPosition(posUp.x, posUp.y);
	pipeUp->SetSize(60, 300);
	pipeUp->SetColliderSize(30, 150);
	m_listPipeUp.push_back(pipeUp);

}

void GSPlay1::CreatRandomPipeDown(int x)
{
	Vector2 posDown;
	posDown.x = 800;
	posDown.y = 400 + x;


	for (auto pipe : m_listPipeDown)
	{
		if (!pipe->IsActive())
		{
			pipe->SetActive(true);
			pipe->Set2DPosition(posDown);
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture1 = ResourceManagers::GetInstance()->GetTexture("pipeDown");

	std::shared_ptr<Pipe> pipeDown = std::make_shared<Pipe>(model, shader, texture1);
	pipeDown->Set2DPosition(posDown.x, posDown.y);
	pipeDown->SetSize(60, 300);
	pipeDown->SetColliderSize(30, 150);
	m_listPipeDown.push_back(pipeDown);

}
