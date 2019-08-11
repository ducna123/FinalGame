#include <sstream>
#include <iomanip>
#include <thread>

#include "GSPlay.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Text.h"
#include "ExplosiveEffect.h"

int screenWidth = 800; //need get on Graphic engine
int screenHeight = 480; //need get on Graphic engine

int GSPlay::m_score = 0;
float timePlus;

bool isDead = false;
GSPlay::GSPlay()
{
	m_SpawnCooldown = 1.5;
	m_SpawnCooldown1 = 1.5;
	timePlus = 7;
	m_score = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{

	isDead = false;

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


	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score1 = std::make_shared< Text>(shader, font, "score: 0", TEXT_COLOR::RED, 1.0);
	m_score1->Set2DPosition(Vector2(5, 25));

	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Bird");
	m_Bird = std::make_shared<Bird >(model, shader, texture);
	m_Bird->Set2DPosition(300, screenHeight / 2);
	m_Bird->SetSize(50, 37);
	m_Bird->SetColliderSize(20);

	texture = ResourceManagers::GetInstance()->GetTexture("over");
	m_Over = std::make_shared<Bird >(model, shader, texture);
	m_Over->SetSize(495, 249);
	m_Over->Set2DPosition(-400, -240);

	texture = ResourceManagers::GetInstance()->GetTexture("replay");
	m_Replay = std::make_shared<GameButton>(model, shader, texture);
	m_Replay->Set2DPosition(-400, -240);
	m_Replay->SetSize(200, 80);
	m_Replay->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		SoundManager::GetInstance()->PauseSound("BG");
		});

	texture = ResourceManagers::GetInstance()->GetTexture("menu");
	m_Menu = std::make_shared<GameButton>(model, shader, texture);
	m_Menu->Set2DPosition(-400, -240);
	m_Menu->SetSize(200, 80);
	m_Menu->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});


	//init sound
	SoundManager::GetInstance()->AddSound("Fly");
	SoundManager::GetInstance()->AddSound("Ping");
	SoundManager::GetInstance()->AddSound("Dead");
	SoundManager::GetInstance()->AddSound("BG");
	

	SoundManager::GetInstance()->PlaySound("BG");

}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPlay::HandleMouseEvents(int x, int y)
{
	//m_Player->MoveToPossition(Vector2(x, y));
}


void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!bIsPressed) {
		if (m_Bird->IsAlive()) {
			SoundManager::GetInstance()->PlaySound("Fly");
			m_Bird->Fly(0.5);
		}
		(m_Replay)->HandleTouchEvents(x, y, bIsPressed);
		(m_Menu)->HandleTouchEvents(x, y, bIsPressed);
	}

	
}



void GSPlay::Update(float deltaTime)
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
			std::cout << a << std::endl;

			CreatRandomPipeDown(a);
			CreatRandomPipeUp(a);
			m_SpawnCooldown = 3;
		}

		if (timePlus > 0) timePlus -= deltaTime;
		if (timePlus <= 0) {
			SoundManager::GetInstance()->PlaySound("Ping");
			m_Bird->PlusPoint();
			std::stringstream stream;
			stream << std::fixed << std::setprecision(0) << m_Bird->GetPoint();
			std::string score = "score: " + stream.str();
			m_score1->setText(score);
			timePlus = 2.5;
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
	else {
		Vector2 pos = m_Bird->Get2DPosition();

		if (isDead == false)
		{
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			auto texture = ResourceManagers::GetInstance()->GetTexture("birdDead");
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			m_Bird = std::make_shared<Bird >(model, shader, texture);
			m_Bird->SetSize(50, 37);
			m_Bird->Set2DPosition(pos);
			m_Bird->SetIsAlive(false);
			SoundManager::GetInstance()->PlaySound("Dead");
			isDead = true;
			SpawnExplosive(Vector2(pos.x+50,pos.y));

			m_Over->Set2DPosition(400, 240);
			m_Replay->Set2DPosition(480, 230);
			m_Menu->Set2DPosition(480, 315);

		}
		m_Bird->Dead();
	}


	if (m_Bird->IsAlive())
	{
		m_Bird->Update(deltaTime);
		m_Bird->CheckColider(m_listPipeUp, m_listPipeDown);
	}

	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			
			exp->Update(deltaTime);
		}
	}


}

void GSPlay::Draw()
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
	m_score1->Draw();
	for (auto exp : m_listExplosiveEffect)
	{
		if (exp->IsActive())
		{
			exp->Draw();
		}
	}
	m_Over->Draw();
	m_Replay->Draw();
	m_Menu->Draw();


}

void GSPlay::CreateRandomEnermy()
{

	
}

void GSPlay::SpawnExplosive(Vector2 pos)
{
	for (auto exp : m_listExplosiveEffect)
	{
		if (!exp->IsActive())
		{
			exp->SetActive(true);
			exp->Set2DPosition(pos);
			return;
		}
	}

	//animation
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("explosive");
	auto shader = ResourceManagers::GetInstance()->GetShader("SpriteShader");
	std::shared_ptr<ExplosiveEffect> exp = std::make_shared<ExplosiveEffect>(model, shader, texture, 
Vector2(960, 768), Vector2(192, 192), 0, 19, 0.7);
	exp->SetSize(100, 100);
	exp->Set2DPosition(pos);
	m_listExplosiveEffect.push_back(exp);
}

void GSPlay::CreatRandomPipeUp(int x)
{
	Vector2 posUp;
	posUp.x = 800;
	posUp.y = 0 + x;


	for (auto pipe : m_listPipeUp)
	{
		if (!pipe->IsActive())
		{
			if (x > 20) pipe->SetMoveY(true);
			pipe->SetActive(true);
			pipe->checkColider = true;
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
	pipeUp->SetColliderSize(25, 145);
	m_listPipeUp.push_back(pipeUp);

}

void GSPlay::CreatRandomPipeDown(int x)
{
	Vector2 posDown;
	posDown.x = 800;
	posDown.y = 400 + x;


	for (auto pipe : m_listPipeDown)
	{
		if (!pipe->IsActive())
		{
			if (x > 20) pipe->SetMoveY(true);
			pipe->SetActive(true);
			pipe->Set2DPosition(posDown);
			pipe->checkColider = true;
			return;
		}
	}

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture1 = ResourceManagers::GetInstance()->GetTexture("pipeDown");

	std::shared_ptr<Pipe> pipeDown = std::make_shared<Pipe>(model, shader, texture1);
	pipeDown->Set2DPosition(posDown.x, posDown.y);
	pipeDown->SetSize(60, 300);
	pipeDown->SetColliderSize(25, 145);
	m_listPipeDown.push_back(pipeDown);

}

