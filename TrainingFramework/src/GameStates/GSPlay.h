#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "../../Bird.h"

class Player;
class Bullet;
class Enermy;
class Text;
class ExplosiveEffect;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init()override;
	void Exit()override;

	void Pause()override;
	void Resume()override;

	void HandleEvents() override;
	void HandleKeyEvents(int key, bool bIsPressed) override;
	void HandleMouseEvents(int x, int y) override;

	void HandleTouchEvents(int x, int y, bool bIsPressed) override;
	void Update(float deltaTime) override;
	void Draw() override;

	void CreatRandomPipeUp(int x);
	void CreatRandomPipeDown(int x);
	
	static int m_score;

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::vector<std::shared_ptr<ExplosiveEffect>> m_listExplosiveEffect;

	float m_SpawnCooldown;
	void CreateRandomEnermy();
	void SpawnExplosive(Vector2 pos);

	float m_SpawnCooldown1;


	std::shared_ptr<Sprite2D> m_BackGround1;
	std::shared_ptr<Sprite2D> m_Land;
	std::shared_ptr<Sprite2D> m_Over;
	std::shared_ptr<GameButton> m_Replay;
	std::shared_ptr<GameButton> m_Menu;

	std::shared_ptr<Sprite2D> m_Pipe1;
	std::shared_ptr<Sprite2D> m_Pipe2;

	std::list<std::shared_ptr<Pipe>> m_listPipeUp;
	std::list<std::shared_ptr<Pipe>> m_listPipeDown;
	std::shared_ptr<Bird> m_Bird;
	std::shared_ptr<Text>  m_score1;


};

