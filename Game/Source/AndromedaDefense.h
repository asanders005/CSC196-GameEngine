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

private:
	eState m_state{ eState::Title };
	float m_spawnTimer = 0;
	float m_spawnTime = 0;

	int m_expBase = 0;
	float m_expScale = 0;

	int m_upgradesSelected[3] = { 0, 0, 0 };
	int m_upgradeHover = 0;

	int m_gamestage = 0;
};