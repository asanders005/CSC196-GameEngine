#pragma once
#include "Game.h"
#include "Text.h"
#include "Particle.h"
#include <map>
#include <vector>
#include <memory>

class Vector2;

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

	void OnPlayerDeath();

	void AddExplosion(Vector2 position, Color color);

	void SpawnPlayer();
	void SpawnRammer();
	void SpawnShooter();

	void SpawnHealthPickup(Vector2 location);
	void SpawnPointPickup(Vector2 location);

private:
	Font* m_font{ nullptr };
	Font* m_lgFont{ nullptr };
	std::map<std::string, Text*> m_text;

	eState m_state{ eState::Title };
	float m_spawnTimer = 0;
	float m_spawnTime = 0;

	float m_stateTimer = 0;

	float m_gameTime = 0;

	int m_expBase = 0;
	float m_expScale = 0;

	bool m_upgradeable[9] = { true,  true,  true,  true,  true,  true,  true,  true,  true };
	int m_upgradesSelected[3] = { -1, -1, -1 };
	int m_upgradeHover = 0;

	int m_gamestage = 0;

	std::string m_recordFile = "AndromedaHighScore.txt";
	int m_highscore = 0;
	int m_hightime = 0;
};