#pragma once
#include "Game.h"

class AndromedaDefense : public Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		Game,
		Pause,
		LevelUp,
		UpgradeSelection,
		PlayerDead,
		GameOver
	};
public:
	AndromedaDefense(Engine* engine) : Game{ engine } {}

	bool Initialize() override;
	void Shutdown() override;
	void Update(float dt) override;

	void Draw(Renderer& renderer) override;

	void SpawnPlayer();
	void SpawnRammer();
	void SpawnShooter();

private:
	eState m_state{ eState::Title };
	float m_spawnTimer = 0;
	float m_spawnTime = 0;

	float m_gameTime = 0;

	int m_expBase = 0;
	float m_expScale = 0;

	bool m_upgradeable[9] = { true,  true,  true,  true,  true,  true,  true,  true,  true };
	int m_upgradesSelected[3] = { -1, -1, -1 };
	int m_upgradeHover = 0;

	int m_gamestage = 0;
};