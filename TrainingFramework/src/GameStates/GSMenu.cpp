#include "GSMenu.h"

GSMenu::GSMenu()
{

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("BGDay");
	
	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(Application::screenWidth / 2, Application::screenHeight / 2);
	m_BackGround->SetSize(Application::screenWidth, Application::screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("Flappy");
	m_Tittle = std::make_shared<Sprite2D>(model, shader, texture);
	m_Tittle->Set2DPosition(400, 106);
	m_Tittle->SetSize(Application::screenWidth/2 -80, 120);

	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 230);
	button->SetSize(200, 80);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("quit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Application::screenWidth / 2, 350);
	button->SetSize(200,80);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);


	/*text game title*/
	/*shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Text_gameName = std::make_shared< Text>(shader, font, "FLAPPY BIRD", TEXT_COLOR::GREEN, 1.0);
	m_Text_gameName->Set2DPosition(Vector2(Application::screenWidth / 2 - 80, 120));*/
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::HandleMouseEvents(int x, int y)
{
}

void GSMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	m_Tittle->Draw();

	for (auto it : m_listButton)
	{
		it->Draw();
	}
	//m_Text_gameName->Draw();
}
