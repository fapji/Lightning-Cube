#include "pch.h"
#include "Level.h"

Level::Level()
{
}

void Level::GiveLevel(LevelState g_CurrentLevel)
{
	m_LevelState = g_CurrentLevel;
}

Level::LevelState Level::Getlevel()
{
	return m_LevelState;
}
