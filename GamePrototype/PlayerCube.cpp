#include "pch.h"
#include "PlayerCube.h"
#include "Game.h"
#include <iostream>

void PlayerCube::nextLevel(int& level)
{
	++level;
}

PlayerCube::PlayerCube(Rectf viewPort)
{
	m_LazerHeigth = viewPort.height / 2 - m_PlayerHeigth;
	m_ShootGuy = Rectf(viewPort.width / 2 - m_PlayerWidth / 2, viewPort.height / 2 - m_PlayerHeigth / 2, m_PlayerWidth, m_PlayerHeigth);
	m_Lazer = Rectf(viewPort.width / 2 - m_LazerWidth / 2, viewPort.height / 2 + m_PlayerHeigth / 2, m_LazerWidth, m_LazerHeigth);

	m_Velocity = Vector2f(0, 0);

	m_Score = 0;
	m_CurrentLevel = 0;
}

void PlayerCube::Draw()
{
	utils::SetColor(Color4f(255, 255, 0, 1));
	utils::DrawRect(m_Lazer);
	utils::SetColor(Color4f(0, 0, 200, 1));
	utils::DrawRect(m_ShootGuy);
}

void PlayerCube::update(float elapsedSec, Rectf viewPort)
{
	switch (m_CurrentLevel)
	{
	case 0:
		break;
	case 1:
	case 2:
	case 4:
	case 5:
		if (m_Score < 5 && m_IsMovingRight)
		{
			m_Velocity.x = 250;
		}
		else if (m_Score < 5 && !m_IsMovingRight)
		{
			m_Velocity.x = -250;

		}
		else if (m_Score >= 5 && m_IsMovingRight)
		{
			m_Velocity.x = 500;
		}
		else if (m_Score >= 5 && !m_IsMovingRight)
		{
			m_Velocity.x = -500;
		}

		m_ShootGuy.left += m_Velocity.x * elapsedSec;
		m_Lazer.left += m_Velocity.x * elapsedSec;

		if (m_ShootGuy.left <= 0)
		{
			m_IsMovingRight = true;
			m_ShootGuy.left = 1;
			m_Lazer.left = 11;
		}
		if (m_ShootGuy.left + m_ShootGuy.width >= viewPort.width)
		{
			m_IsMovingRight = false;
			m_ShootGuy.left = viewPort.width - m_ShootGuy.width - 1;
			m_Lazer.left = viewPort.width - m_ShootGuy.width + 9;
		}
		break;
	case 3:
		m_ShootGuy = Rectf(viewPort.width / 2 - m_PlayerWidth / 2, viewPort.height / 2 - m_PlayerHeigth / 2, m_PlayerWidth, m_PlayerHeigth);
		m_Lazer = Rectf(viewPort.width / 2 - m_LazerWidth / 2, viewPort.height / 2 + m_PlayerHeigth / 2, m_LazerWidth, m_LazerHeigth);
		break;
	default:
		std::cout << "How Did you get here ??!? \n";
		break;
	}
}

Rectf PlayerCube::GetLazer()
{
	return m_Lazer;
}

void PlayerCube::TakeScoreAndLevel(int score, int currentLevel)
{
	m_Score = score;
	m_CurrentLevel = currentLevel;
}
