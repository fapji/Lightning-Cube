#pragma once
#include "utils.h"
#include "Texture.h"
#include "SoundStream.h"
#include <vector>

class EnemyCube
{
public:
	
	void nextLevel(int& level);


	EnemyCube(Rectf viewPort);
	~EnemyCube();

	void Draw(Rectf viewPort);
	void Update(float elapsedSec, Rectf viewPort, Rectf lazer);
	void CheckHit(SDL_KeyboardEvent e, Rectf lazer);

	const Rectf& GetRect();

	const int GetScore();
	const int GetLevel();

private:

	const float m_EnemyWidth{ 40 };
	const float m_EnemyHeigth{ 40 };
	Rectf m_EnemyCube;

	const float m_livesRad{ 5 };
	Ellipsef m_LivesCircle;

	const float m_SndEnemyWidth{ 40 };
	const float m_SndEnemyHeigth{ 40 };
	Rectf m_SndEnemyCube;

	const float m_SndlivesRad{ 5 };
	Ellipsef m_SndLivesCircle;
	
	bool m_IsOverlapping{ false };
	bool m_HasBeenHit{ false };
	bool m_IsShowingHit{ false };

	bool m_SndIsOverlapping{ false };
	bool m_SndHasBeenHit{ false };
	bool m_SndIsShowingHit{ false };

	float m_HitDisplayCounter{ 0 };
	float m_SndHitDisplayCounter{ 0 };

	int m_Score;
	int m_CurrentLevel;

	int m_AllowedMisses{ 6 };
	int m_MisCounter{ 11 };

	int m_SndMisCounter{ 11 };

	Vector2f m_EnemyVelocity{ 200,0 };
	float m_StartingVelocity;
	float m_SpeedChange{ 1.3 };
	
	Vector2f m_SndEnemyVelocity{ 120,0 };
	float m_SndStartingVelocity;
	float m_SndSpeedChange{ 1.35 };

	Color4f m_StringTextureColor;

	Texture* m_pScoreText;
	Texture* m_pHpText;
	Texture* m_pSndHpText;
	Texture* m_pLevelText;

	
	Texture* m_pSpeedText;
	Texture* m_pSndSpeedText;

	std::vector<Texture*> m_pNumberTextures;
	std::vector<int> m_LevelChars;
	std::vector<int> m_ScoreChars;
	std::vector<int> m_SpeedChars;
	std::vector<int> m_SndSpeedChars;


	SoundStream* m_pSoundEffect;
	bool m_SoundIsOn;
	Texture* m_pSoundInstructionsText;
	const float m_SoundCubeWidth{ 10 };
	const float m_SoundCubeHeigth{ 10 };
	Rectf m_SoundCube;

	Texture* m_pControllsText;
};

