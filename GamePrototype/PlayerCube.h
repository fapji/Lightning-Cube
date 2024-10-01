#pragma once
#include "utils.h"

class PlayerCube
{
public:
	void nextLevel(int& level);


	PlayerCube(Rectf viewPort);
	void Draw();
	void update(float elapsedSec, Rectf viewPort);
	
	Rectf GetLazer();
	void TakeScoreAndLevel(int score, int currentLevel);

private:
	

	const float m_PlayerWidth{ 40 };
	const float m_PlayerHeigth{ 40 };
	Rectf m_ShootGuy;

	const float m_LazerWidth{ 20 };
	float m_LazerHeigth{ 0 };
	Rectf m_Lazer;

	Vector2f m_Velocity;
	bool m_IsMovingRight{ true };

	int m_Score;
	int m_CurrentLevel;

};

