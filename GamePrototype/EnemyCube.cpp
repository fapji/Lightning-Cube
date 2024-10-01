#include "pch.h"
#include "EnemyCube.h"
#include "iostream"
#include "Game.h"
#include <cstdlib>

void EnemyCube::nextLevel(int& level)
{
	++level;
}

EnemyCube::EnemyCube(Rectf viewPort)
{
	m_Score = 0;
	m_CurrentLevel = 0;

	m_EnemyCube = Rectf(1, viewPort.height - m_EnemyHeigth - 21, m_EnemyWidth, m_EnemyHeigth);
	m_LivesCircle = Ellipsef(viewPort.width / 4, viewPort.height / 5 * 2 + 10, m_livesRad, m_livesRad);

	m_SndEnemyCube = Rectf(1, viewPort.height - m_SndEnemyHeigth - 100, m_SndEnemyWidth, m_SndEnemyHeigth);
	m_SndLivesCircle = Ellipsef(viewPort.width / 4, viewPort.height / 5 * 2 -30, m_livesRad, m_livesRad);

	m_StartingVelocity = 200;
	m_SndStartingVelocity = 150;

	m_StringTextureColor = Color4f(1, 1, 1, 1);

	m_pNumberTextures = std::vector<Texture*>();
	m_ScoreChars = std::vector<int>();


	m_pScoreText = new Texture("Score:", "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor);

	m_pSpeedText = new Texture("Red Speed:", "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor);
	m_pSndSpeedText = new Texture("Green Speed:", "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor);

	m_pHpText = new Texture("Red Hp:", "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor);
	m_pSndHpText = new Texture("Green Hp:", "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor);

	m_pLevelText = new Texture("Level:", "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor);

	for (size_t i = 0; i < 10; i++)
	{
		m_pNumberTextures.push_back(new Texture(std::to_string(i), "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor));
	}

	m_pControllsText = new Texture("Spacebar To Play!", "Qdbettercomicsans-jEEeG.ttf", 20, m_StringTextureColor);

	m_pSoundInstructionsText = new Texture("Toggle Sound Effect = s", "Qdbettercomicsans-jEEeG.ttf", 14, m_StringTextureColor);
	m_SoundCube = Rectf(viewPort.width / 2 - 70, viewPort.height / 6 - 16, m_SoundCubeWidth, m_SoundCubeHeigth); //Update Position to be Allighned when ready
	m_pSoundEffect = new SoundStream("DeadByDaylightSkillCheckSoundEffect.mp3");
	m_SoundIsOn = true;

}

EnemyCube::~EnemyCube()
{
	delete m_pScoreText;

	delete m_pSpeedText;
	delete m_pSndSpeedText;

	delete m_pHpText;
	delete m_pSndHpText;

	delete m_pLevelText;

	m_pScoreText = nullptr;

	m_pSpeedText = nullptr;
	m_pSndSpeedText = nullptr;

	m_pHpText = nullptr;
	m_pSndHpText = nullptr;

	m_pLevelText = nullptr;

	for (Texture* ScoreTexture : m_pNumberTextures)
	{
		delete ScoreTexture;
		ScoreTexture = nullptr;
	}

	delete m_pControllsText;
	m_pControllsText = nullptr;

	delete m_pSoundEffect;
	m_pSoundEffect = nullptr;
}

void EnemyCube::Draw(Rectf viewPort)
{
	//Display Level
	m_pLevelText->Draw(Point2f(viewPort.width / 10, viewPort.height / 10 * 1.5));
	for (int i = 0; i < m_LevelChars.size(); i++)
	{
		m_pNumberTextures[m_LevelChars[i]]->Draw(Point2f(viewPort.width / 10 + 50 + i * 20, viewPort.height / 10 * 1.5));
	}
	
	//Display Score
	m_pScoreText->Draw(Point2f(viewPort.width / 2 - 35, viewPort.height / 5 * 2));
	for (int i = 0; i < m_ScoreChars.size(); i++)
	{
		m_pNumberTextures[m_ScoreChars[i]]->Draw(Point2f(viewPort.width / 2 + 25 + i * 20, viewPort.height / 5 * 2));
	}

	//Display Controlls
	m_pControllsText->Draw(Point2f(viewPort.width / 2 -50, viewPort.height / 6 + 20));

	m_pSoundInstructionsText->Draw(Point2f(viewPort.width / 2 - 50, viewPort.height / 6 - 20));
	if (m_SoundIsOn)
	{
		utils::SetColor(Color4f(0, 255, 0, 1));
	}
	else
	{
		utils::SetColor(Color4f(255, 0, 0, 1));
	}
	utils::FillRect(m_SoundCube);

	// Display Speed 
	m_pSpeedText->Draw(Point2f(viewPort.width / 4 * 2.8, viewPort.height / 5 * 2));
	for (int i = 0; i < m_SpeedChars.size(); i++)
	{
		m_pNumberTextures[m_SpeedChars[i]]->Draw(Point2f(viewPort.width / 4 * 2.8 + 110 + i * 20, viewPort.height / 5 * 2));
	}

	//Second cube Speed
	switch (m_CurrentLevel)
	{
	case 3:
	case 4:
	case 5:
		m_pSndSpeedText->Draw(Point2f(viewPort.width / 4 * 2.8 -20, viewPort.height / 5 * 1.5));
		for (int i = 0; i < m_SndSpeedChars.size(); i++)
		{
			m_pNumberTextures[m_SndSpeedChars[i]]->Draw(Point2f(viewPort.width / 4 * 2.8 + 110 + i * 20, viewPort.height / 5 * 1.5));
		}
	default:
		break;
	}

	//Display Hp
	//Cube 1
	m_pHpText->Draw(Point2f(viewPort.width / 4 - 100, viewPort.height / 5 * 2));
	for (int i = 0; i < m_AllowedMisses; i++)
	{
		if (i < m_MisCounter)
		{
			utils::SetColor(Color4f(0, 255, 0, 1));
		}
		else
		{
			utils::SetColor(Color4f(255, 0, 0, 1));
		}
		m_LivesCircle.center.x = viewPort.width / 4 + 13 * i;
		utils::FillEllipse(m_LivesCircle);
	}

	//Cube 2
	switch (m_CurrentLevel)
	{
	case 3:
	case 4:
	case 5:
		m_pSndHpText->Draw(Point2f(viewPort.width / 4 - 120, viewPort.height / 5 * 2 - 40));
		for (int i = 0; i < m_AllowedMisses; i++)
		{
			if (i < m_SndMisCounter)
			{
				utils::SetColor(Color4f(0, 255, 0, 1));
			}
			else
			{
				utils::SetColor(Color4f(255, 0, 0, 1));
			}
			m_SndLivesCircle.center.x = viewPort.width / 4 + 13 * i;
			utils::FillEllipse(m_SndLivesCircle);
		}

		break;
	default:
		break;
	}

	utils::SetColor(Color4f(255, 255, 255, 1));



	//Cube 1
	if (m_IsShowingHit)
	{
		utils::SetColor(Color4f(255, 255, 255, 1));
	}
	else
	{
		utils::SetColor(Color4f(255, 0, 0, 1));
	}
	utils::DrawRect(m_EnemyCube);


	//Cube 2
	switch (m_CurrentLevel)
	{
	case 3:
	case 4:
	case 5:
		//Cube 2
		if (m_SndIsShowingHit)
		{
			utils::SetColor(Color4f(255, 255, 255, 1));
		}
		else
		{
			utils::SetColor(Color4f(0, 255, 0, 1));
		}
		utils::DrawRect(m_SndEnemyCube);
		utils::SetColor(Color4f(0, 255, 0, 1));
		break;
	default:
		break;
	}
}

void EnemyCube::Update(float elapsedSec, Rectf viewPort, Rectf lazer)
{
	//Level Display
	const std::string level = std::to_string(m_CurrentLevel + 1);
	m_LevelChars.clear();
	for (size_t i = 0; i < level.length(); i++)
	{
		m_LevelChars.push_back((int)(level[i] - '0'));
	}

	//Score display
	const std::string score = std::to_string(m_Score);
	m_ScoreChars.clear();
	for (size_t i = 0; i < score.length(); i++)
	{
		m_ScoreChars.push_back((int)(score[i] - '0'));
	}

	//no longer universal
	//Cube 1
	const std::string speed = std::to_string((int)m_EnemyVelocity.Length());
	m_SpeedChars.clear();
	for (size_t i = 0; i < speed.length(); i++)
	{
		m_SpeedChars.push_back((int)(speed[i] - '0'));
	}

	//Cube 2
	const std::string speed2 = std::to_string((int)m_SndEnemyVelocity.Length());
	m_SndSpeedChars.clear();
	for (size_t i = 0; i < speed2.length(); i++)
	{
		m_SndSpeedChars.push_back((int)(speed2[i] - '0'));
	}
	

	//Cube 1
	//x checks
	if (m_EnemyCube.left <= 0)
	{
		m_EnemyCube.left = 1;
		m_EnemyVelocity.x *= -1;
	}
	else if (m_EnemyCube.left >= viewPort.width - m_EnemyCube.width)
	{
		m_EnemyCube.left = viewPort.width - m_EnemyCube.width - 1;
		m_EnemyVelocity.x *= -1;
	}
	//y checks
	if (m_EnemyCube.bottom + m_EnemyCube.height >= lazer.bottom + lazer.height)
	{
		m_EnemyCube.bottom = lazer.bottom + lazer.height - m_EnemyCube.height - 1;
		m_EnemyVelocity.y *= -1;
	}
	else if (m_EnemyCube.bottom <= lazer.bottom)
	{
		m_EnemyCube.bottom = lazer.bottom + 1;
		m_EnemyVelocity.y *= -1;
	}

	//Cube 2
	switch (m_CurrentLevel)
	{
	case 3:
	case 4:
		if (m_SndEnemyCube.left <= 0)
		{
			m_SndEnemyCube.left = 1;
			m_SndEnemyVelocity.x *= -1;
		}
		else if (m_SndEnemyCube.left >= viewPort.width - m_SndEnemyCube.width)
		{
			m_SndEnemyCube.left = viewPort.width - m_SndEnemyCube.width - 1;
			m_SndEnemyVelocity.x *= -1;
		}
		break;
	case 5:
		if (m_SndEnemyCube.left <= 0)
		{
			m_SndEnemyCube.left = 1;
			m_SndEnemyVelocity.x *= -1;
		}
		else if (m_SndEnemyCube.left >= viewPort.width - m_SndEnemyCube.width)
		{
			m_SndEnemyCube.left = viewPort.width - m_SndEnemyCube.width - 1;
			m_SndEnemyVelocity.x *= -1;
		}
		// code that does checks for the y
		if (m_SndEnemyCube.bottom + m_SndEnemyCube.height >= lazer.bottom + lazer.height)
		{
			m_SndEnemyCube.bottom = lazer.bottom + lazer.height - m_SndEnemyCube.height - 1;
			m_SndEnemyVelocity.y *= -1;
		}
		else if (m_SndEnemyCube.bottom <= lazer.bottom)
		{
			m_SndEnemyCube.bottom = lazer.bottom + 1;
			m_SndEnemyVelocity.y *= -1;
		}
		break;
	default:
		break;
	}

	//Decreases MissCounter And resets Overlapping and Hit Values
	//Cube 1
	if (m_IsOverlapping == false && utils::IsOverlapping(m_EnemyCube, lazer))
	{
		m_IsOverlapping = true;
		m_MisCounter--;
	}
	else if (utils::IsOverlapping(m_EnemyCube, lazer) == false)
	{
		m_IsOverlapping = false;
		m_HasBeenHit = false;
	}

	// cube 2
	if (m_SndIsOverlapping == false && utils::IsOverlapping(m_SndEnemyCube, lazer))
	{
		m_SndIsOverlapping = true;
		m_SndMisCounter--;
	}
	else if (utils::IsOverlapping(m_SndEnemyCube, lazer) == false)
	{
		m_SndIsOverlapping = false;
		m_SndHasBeenHit = false;
	}

	//Decreases Score When Too many Misses
	if (m_Score > 0)
	{
		//Cube 1
		if (m_MisCounter <= 0)
		{
			--m_Score;
			m_MisCounter = m_AllowedMisses + 1;
		}

		//Cube 2
		switch (m_CurrentLevel)
		{
		case 3:
		case 4:
		case 5:
			if (m_SndMisCounter <= 0)
			{
				--m_Score;
				m_SndMisCounter = m_AllowedMisses + 1;
			}
		default:
			break;
		}
	}

	//Updates The White flash when a cube has been hit
	//Cube 1
	if (m_IsShowingHit)
	{
		m_HitDisplayCounter += elapsedSec;
	}
	if (m_HitDisplayCounter >= 0.25)
	{
		m_IsShowingHit = false;
		m_HitDisplayCounter = 0;
	}
	
	//Cube 2
	if (m_SndIsShowingHit)
	{
		m_SndHitDisplayCounter += elapsedSec;
	}
	if (m_SndHitDisplayCounter >= 0.25)
	{
		m_SndIsShowingHit = false;
		m_SndHitDisplayCounter = 0;
	}

	//Updates Cube Speed
	//Cube 1
	
	if (m_EnemyVelocity.x > 0)
	{
		m_EnemyVelocity.x = m_StartingVelocity * std::pow(m_SpeedChange, m_Score);
	}
	else if (m_EnemyVelocity.x < 0)
	{
		m_EnemyVelocity.x = m_StartingVelocity * -std::pow(m_SpeedChange, m_Score);
	}


	//Update Cube 1 Position
	m_EnemyCube.left += m_EnemyVelocity.x * elapsedSec;

	//Cube 2
	switch (m_CurrentLevel)
	{
	case 3:
	case 4:
		
		if (m_SndEnemyVelocity.x > 0)
		{
			m_SndEnemyVelocity.x = m_SndStartingVelocity *  std::pow(m_SndSpeedChange, m_Score);
		}
		else if (m_SndEnemyVelocity.x < 0)
		{
			m_SndEnemyVelocity.x = m_SndStartingVelocity * -std::pow(m_SndSpeedChange, m_Score);
		}
		//Update Cube 2 position
		m_SndEnemyCube.left += m_SndEnemyVelocity.x * elapsedSec;
		break;
	case 5:
		if (m_SndEnemyVelocity.x > 0)
		{
			m_SndEnemyVelocity.x = m_SndStartingVelocity * std::pow(m_SndSpeedChange, m_Score);
		}
		else if (m_SndEnemyVelocity.x < 0)
		{
			m_SndEnemyVelocity.x = m_SndStartingVelocity * -std::pow(m_SndSpeedChange, m_Score);
		}


		//Sets y velocity
		if (m_Score < 5)
		{
			if (m_EnemyVelocity.y > 0)
			{
				m_EnemyVelocity.y = 50;
			}
			else if (m_EnemyVelocity.y < 0)
			{
				m_EnemyVelocity.y = -50;
			}

			if (m_SndEnemyVelocity.y > 0)
			{
				m_SndEnemyVelocity.y = 25;
			}
			else if (m_SndEnemyVelocity.y < 0)
			{
				m_SndEnemyVelocity.y = -25;
			}
		}
		else if (m_Score >= 5)
		{
			if (m_EnemyVelocity.y > 0)
			{
				m_EnemyVelocity.y = 75;

			}
			else if (m_EnemyVelocity.y < 0)
			{
				m_EnemyVelocity.y = -75;
			}

			if (m_SndEnemyVelocity.y > 0)
			{
				m_SndEnemyVelocity.y = 100;
			}
			else if (m_SndEnemyVelocity.y < 0)
			{
				m_SndEnemyVelocity.y = -100;
			}
		}

		//Update Cube 2 Position
		m_SndEnemyCube.left += m_SndEnemyVelocity.x * elapsedSec;
		m_SndEnemyCube.bottom += m_SndEnemyVelocity.y * elapsedSec;
		m_EnemyCube.bottom += m_EnemyVelocity.y * elapsedSec;

		break;
	default:
		break;
	}

	//Level increase
	if (m_Score >= 10)
	{
		m_Score = 0;
		if (m_EnemyVelocity.x < 0)
		{
			m_EnemyVelocity.x = m_StartingVelocity;
		}
		else if (m_EnemyVelocity.x > 0)
		{
			m_EnemyVelocity.x = -m_StartingVelocity;
		}

		//on level transition makes 2nd cube spawn random
		switch (m_CurrentLevel)
		{
		case 2:
			m_SndEnemyCube.left = rand() % (int)viewPort.width;
			break;
		case 4:
			m_EnemyVelocity.y = -1;
			m_SndEnemyVelocity.y = -1;
			break;
		default:
			break;
		}

		nextLevel(m_CurrentLevel);
	}
}



void EnemyCube::CheckHit(SDL_KeyboardEvent e, Rectf lazer)
{
	switch (e.keysym.sym)
	{
	case SDLK_SPACE:
		//Cube 1
		if (m_HasBeenHit == false && utils::IsOverlapping(m_EnemyCube, lazer))
		{
			m_HasBeenHit = true;

			if (m_SoundIsOn)
			{
				m_pSoundEffect->Play(false);
			}

			++m_Score;
			m_MisCounter = m_AllowedMisses + 1;
			m_IsShowingHit = true;
			switch (m_CurrentLevel)
			{
			case 2:
			case 4:
				if (rand() % 2 == 1)
				{
					m_EnemyVelocity.x *= -1;
				}
				break;
			case 5:
				//Cube 1
				if (rand() % 2 == 1)
				{
					m_EnemyVelocity.x *= -1;
				}
				//Cube 2
				if (rand() % 2 == 1)
				{
					m_SndEnemyVelocity.x *= -1;
				}
				break;
			default:
				break;
			}
		}
		else if (!utils::IsOverlapping(m_SndEnemyCube, lazer))
		{
			if (m_Score > 0)
			{
				m_MisCounter = m_AllowedMisses + 1;
				//m_EnemyVelocity.x /= m_SpeedChange;
				--m_Score;
				//std::system("cls");
			}
		}

		//Cube 2
		switch (m_CurrentLevel)
		{
		case 3:
		case 4:
		case 5:
		if (m_SndHasBeenHit == false && utils::IsOverlapping(m_SndEnemyCube, lazer))
		{
			m_SndHasBeenHit = true;

			if (m_SoundIsOn)
			{
				m_pSoundEffect->Play(false);

			}

			++m_Score;
			m_SndMisCounter = m_AllowedMisses + 1;
			m_SndIsShowingHit = true;
			switch (m_CurrentLevel)
			{
			case 4:
				if (rand() % 2 == 1)
				{
					m_SndEnemyVelocity.x *= -1;
				}
			case 5:
				//Cube 2
				if (rand() % 2 == 1)
				{
					m_SndEnemyVelocity.x *= -1;
				}
				//Cube 1
				if (rand() % 2 == 1)
				{
					m_EnemyVelocity.x *= -1;
				}
				break;
			default:
				break;
			}
		}
		//Score No longer decrements by 2
		else if (!utils::IsOverlapping(m_EnemyCube, lazer))
		{

			if (m_Score > 0)
			{
				m_SndMisCounter = m_AllowedMisses + 1;
				
			}
		}
		break;
		default:
			break;
		}

		break;
	case SDLK_s:
		if (m_SoundIsOn)
		{
			m_SoundIsOn = false;
		}
		else if (!m_SoundIsOn)
		{
			m_SoundIsOn = true;
		}
		break;
	case SDLK_i:
		m_Score = 10;
		break;
	default:
		break;
	}
}



const Rectf& EnemyCube::GetRect()
{
	return m_EnemyCube;
}

const int EnemyCube::GetScore()
{
	return m_Score;
}

const int EnemyCube::GetLevel()
{
	return m_CurrentLevel;
}
