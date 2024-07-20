#include "AndromedaDefense.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "Font.h"
#include "Text.h"
#include <iostream>

bool AndromedaDefense::Initialize()
{
	m_scene = new Scene();

	m_font = new Font();
	m_font->Load("pdark.ttf", 20);
	m_lgFont = new Font();
	m_lgFont->Load("pdark.ttf", 50);

	srand(time(0));

    return true;
}

void AndromedaDefense::Shutdown()
{

}

void AndromedaDefense::Update(float dt)
{
	switch (m_state)
	{
	case eState::Title:
		if (m_text.find("title") == m_text.end())
		{
			m_text.emplace("title", new Text(m_lgFont));
			m_text["title"]->Create(RENDERER, "DEFENSE OF ANDROMEDA", { 1, 1, 1 });
		}
		if (m_text.find("startTxt") == m_text.end())
		{
			m_text.emplace("startTxt", new Text(m_font));
			m_text["startTxt"]->Create(RENDERER, "Press Space to Start", { 1, 1, 1 });
		}
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_text.erase("title");
			m_state = eState::StartGame;
		}
		break;
	case eState::StartGame:
		m_score = 0;

		SpawnPlayer();

		m_expBase = 10;
		m_expScale = 1.1f;

		m_gamestage = 1;

		m_spawnTime = 3;
		m_spawnTimer = m_spawnTime;

		m_state = eState::Game;
		break;
	case eState::Game:
		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			SpawnRammer();
			m_spawnTimer = m_spawnTime;
		}

		if (INPUT.GetKeyPressed(SDL_SCANCODE_V)) m_scene->EraseAll("Enemy");

		if (m_scene->GetActor<Player>()->GetExp() >= (Math::Powf((float)(m_expBase * m_scene->GetActor<Player>()->GetLevel()), m_expScale)))
		{
			m_scene->GetActor<Player>()->ResetExp();
			m_scene->GetActor<Player>()->LevelUp();
			std::cout << "Level Up \n";
			m_state = eState::LevelUp;
		}

		if (m_scene->GetActor<Player>()->GetHP() < 0)
		{
			m_state = eState::PlayerDead;
		}
		break;
	case eState::Pause:
		break;
	case eState::LevelUp:
		{
			int upgradeCount = 0;
			bool upgradeAvailable = false;
			do
			{
				upgradeAvailable = false;
				int temp = random(11);
				if (m_scene->GetActor<Player>()->GetUpgrade(temp) < m_scene->GetActor<Player>()->GetUpgradeLimit(temp))
				{
					m_upgradesSelected[upgradeCount] = temp;
					upgradeCount++;
				}
				for (int i = 0; i < 11; i++)
				{
					if (m_scene->GetActor<Player>()->GetUpgrade(i) < m_scene->GetActor<Player>()->GetUpgradeLimit(i))
					{
						upgradeAvailable = true;
						break;
					}
				}
			} while (upgradeCount < 3 && upgradeAvailable);

			if (upgradeCount < 3)
			{
				if (upgradeCount < 2)
				{
					if (upgradeCount < 1)
					{
						m_upgradesSelected[0] = 13;
					}
					m_upgradesSelected[1] = 12;
				}
				m_upgradesSelected[2] = 11;
			}
		}
		m_state = eState::UpgradeSelection;

		if (m_scene->GetActor<Player>()->GetHP() < 0)
		{
			m_state = eState::PlayerDead;
		}
		break;
	case eState::UpgradeSelection:
		if (INPUT.GetKeyPressed(SDL_SCANCODE_RIGHT) && m_upgradeHover < 2) m_upgradeHover++;
		if (INPUT.GetKeyPressed(SDL_SCANCODE_LEFT) && m_upgradeHover > 0) m_upgradeHover--;
		if (INPUT.GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			int temp = m_upgradesSelected[m_upgradeHover];
			switch (temp)
			{
			case 11:
				m_scene->GetActor<Player>()->SetHP(m_scene->GetActor<Player>()->GetHPMax());
				std::cout << "HP Restore \n";
				break;
			case 12:
				m_score += 1000;
				std::cout << "Score Up \n";
				break;
			case 13:
				m_scene->EraseAll("Enemy");
				std::cout << "Screen Clear \n";
				break;
			default:
				m_scene->GetActor<Player>()->Upgrade(temp);
				std::cout << "Player Upgrade #" << temp << std::endl;
				break;
			}
			m_state = eState::Game;
		}
		break;
	case eState::PlayerDead:
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
	
	if (m_state == eState::Game) m_scene->Update(dt);
}

void AndromedaDefense::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);

	switch (m_state)
	{
	case eState::Title:
		m_text["title"]->Draw(RENDERER, RENDERER.GetWidth() / 2, (int)(RENDERER.GetHeight() / 3));
		m_text["startTxt"]->Draw(RENDERER, RENDERER.GetWidth() / 2, (int)(RENDERER.GetHeight() / 3) * 2);
		break;
	case eState::UpgradeSelection:
		renderer.SetColor(0, 0, 0, 100);
		renderer.DrawRect(RENDERER.GetWidth() / 2, RENDERER.GetHeight() / 2, RENDERER.GetWidth(), RENDERER.GetHeight());
		renderer.SetColor({ 1, 1, 1 });
		renderer.DrawRect((RENDERER.GetWidth() / 4) * (m_upgradeHover + 1), RENDERER.GetHeight() / 2, 360, 760);
		renderer.SetColor({ 0, 0, 0 });
		renderer.DrawRect(RENDERER.GetWidth() / 4, RENDERER.GetHeight() / 2, 300, 700);
		renderer.DrawRect((RENDERER.GetWidth() / 4) * 2, RENDERER.GetHeight() / 2, 300, 700);
		renderer.DrawRect((RENDERER.GetWidth() / 4) * 3, RENDERER.GetHeight() / 2, 300, 700);
		renderer.SetColor({ 1, 1, 1 });
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
}

void AndromedaDefense::SpawnPlayer()
{
	Model* model = new Model{ GameData::playerShipPoints, Color{ 1, 0, 1 } };
	Transform transform{ {RENDERER.GetWidth() / 2, RENDERER.GetHeight() / 2}, 0, 3 };

	Player* player = new Player(3000, 10, transform, model);
	player->SetDamping(3.5f);
	player->SetRDamping(2.5f);
	player->SetDamage(1);
	player->SetTag("Player");
	m_scene->AddActor(player);
}

void AndromedaDefense::SpawnRammer()
{
	Model* model = new Model{ GameData::rammerShipPoints, Color{ 1, 0, 0 } };
	Enemy* enemy{ nullptr };
	switch (random(4))
	{
	case 0:
		enemy = new Enemy(500, Transform{ { randomf(RENDERER.GetWidth()), 0.0f}, 0, 4}, model);
		break;
	case 1:
		enemy = new Enemy(500, Transform{ { (float)RENDERER.GetWidth(), randomf(RENDERER.GetHeight()) }, 0, 4 }, model);
		break;
	case 2:
		enemy = new Enemy(500, Transform{ { randomf(RENDERER.GetWidth()), (float)RENDERER.GetHeight() }, 0, 4 }, model);
		break;
	case 3:
		enemy = new Enemy(500, Transform{ { 0.0f, randomf(RENDERER.GetHeight()) }, 0, 4 }, model);
		break;
	default:
		enemy = new Enemy(500, Transform{ { RENDERER.GetWidth(), RENDERER.GetHeight() }, 0, 4 }, model);
		break;
	}
	enemy->SetDamping(3.5f);
	enemy->SetHP(m_gamestage);
	enemy->SetDamage(m_gamestage);
	//enemy->SetExpValue(m_scene->GetActor<Player>()->GetLevel());
	enemy->SetExpValue(999);
	enemy->SetTag("Enemy");
	m_scene->AddActor(enemy);
}