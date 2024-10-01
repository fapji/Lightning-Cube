#pragma once
class Level
{

public:
	enum class LevelState
	{
		Level1,
		Level2,
		Level3,
		Level4,
	};
	Level();
	void GiveLevel(LevelState g_CurrentLevel);
	LevelState Getlevel();

private:
	LevelState m_LevelState;
};