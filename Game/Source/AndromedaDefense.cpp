#include "AndromedaDefense.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Shooter.h"
#include "GameData.h"
#include "Font.h"
#include "Text.h"
#include "PointPickup.h"
#include <iostream>
#include <fstream>

bool AndromedaDefense::Initialize()
{
	m_scene = new Scene(this);

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
			m_text.emplace("title", new Text(m_lgFont, true));
			m_text["title"]->Create(RENDERER, "DEFENSE OF ANDROMEDA", { 1, 1, 1 });
		}
		if (m_text.find("startTxt") == m_text.end())
		{
			m_text.emplace("startTxt", new Text(m_font, true));
			m_text["startTxt"]->Create(RENDERER, "Press Space to Start", { 1, 1, 1 });
		}
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_text.erase("title");
			m_text.erase("startTxt");
			AUDIO.PlaySound("GameStart.wav");
			m_state = eState::StartGame;
		}
		break;
	case eState::StartGame:
		m_score = 0;

		SpawnPlayer();

		m_expBase = 10;
		m_expScale = 1.1f;

		for (int i = 0; i < sizeof(m_upgradeable); i++)
		{
			m_upgradeable[i] = true;
		}

		m_gamestage = 1;

		m_spawnTime = 2;
		m_spawnTimer = m_spawnTime;

		m_gameTime = 0;

		m_state = eState::Game;
		break;
	case eState::Game:
		m_text.erase("timer");
		m_text.erase("score");
		m_text.erase("hp");
		if (m_text.find("timer") == m_text.end())
		{
			int seconds = (int)m_gameTime % 60;
			int minutes = (int)m_gameTime / 60;
			std::stringstream timer;
			timer << minutes << " " << seconds;
			m_text.emplace("timer", new Text(m_lgFont, true));
			m_text["timer"]->Create(RENDERER, timer.str().c_str(), {1, 1, 1});
		}
		if (m_text.find("score") == m_text.end())
		{
			std::stringstream score;
			score << "Score " << m_score;
			m_text.emplace("score", new Text(m_font));
			m_text["score"]->Create(RENDERER, score.str().c_str(), { 1, 1, 1 });
		}
		if (m_text.find("hp") == m_text.end() && m_scene->GetActor<Player>())
		{
			std::stringstream hp;
			hp << "Life " << m_scene->GetActor<Player>()->GetHP();
			m_text.emplace("hp", new Text(m_font));
			m_text["hp"]->Create(RENDERER, hp.str().c_str(), { 1, 1, 1 });
		}

		m_gameTime += dt;

		m_spawnTimer -= dt;
		if (m_spawnTimer <= 0)
		{
			if (m_gamestage >= 2)
			{
				for (int i = 0; i < random(m_gamestage - 1, m_gamestage * 2); i++)
				{
					if (random(10) == 3)
					{
						SpawnShooter();
					}
					else
					{
						SpawnRammer();
					}
				}
			}
			else
			{
				for (int i = 0; i < random(1, m_gamestage * 3); i++)
				{
					//SpawnShooter();
					SpawnRammer();
				}
			}
			m_spawnTimer = m_spawnTime;
		}

		//if (INPUT.GetKeyPressed(SDL_SCANCODE_V)) m_scene->EraseAll("Enemy");

		if (m_scene->GetActor<Player>())
		{
			if (m_scene->GetActor<Player>()->GetExp() >= (Math::Powf((float)(m_expBase * m_scene->GetActor<Player>()->GetLevel()), m_expScale)))
			{
				m_scene->GetActor<Player>()->ResetExp();
				m_scene->GetActor<Player>()->LevelUp();
				AUDIO.PlaySound("LevelUp.wav");
				//std::cout << "Level Up \n";
				m_state = eState::LevelUp;
			}
			if (m_scene->GetActor<Player>()->GetLevel() / 4 > m_gameTime / 180)
			{
				//std::cout << "Player Gamestage: " << m_gamestage << std::endl;
				m_gamestage = (m_scene->GetActor<Player>()->GetLevel() / 4) + 1;
			}
			else
			{
				//std::cout << "Time Gamestage: " << m_gamestage << std::endl;
				m_gamestage = (m_gameTime / 180) + 1;
			}
		}
		else
		{
			m_state = eState::PlayerDead;
		}
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) m_state = eState::Pause;
		break;
	case eState::Pause:
		if (m_text.find("pause") == m_text.end())
		{
			m_text.emplace("pause", new Text(m_lgFont, true));
			m_text["pause"]->Create(RENDERER, "Pause", {1, 1, 1});
		}
		if (INPUT.GetKeyPressed(SDL_SCANCODE_ESCAPE))
		{
			m_text.erase("pause");
			m_state = eState::Game;
		}
		break;
	case eState::LevelUp:
		if (m_scene->GetActor<Player>())
		{
			int upgradeCount = 0;
			bool upgradeAvailable = false;
			int numUpgradeable = 0;
			do
			{
				int temp = 0;
				do
				{
					temp = random(9);
					upgradeAvailable = true;
					for (int i = 0; i < 2; i++)
					{
						if (temp == m_upgradesSelected[i])
						{
							upgradeAvailable = false;
						}
					}
				} while (!upgradeAvailable);
				if (m_scene->GetActor<Player>()->GetUpgrade(temp) < m_scene->GetActor<Player>()->GetUpgradeLimit(temp))
				{
					m_upgradesSelected[upgradeCount] = temp;
					upgradeCount++;
				}
				numUpgradeable = 0;
    			for (int i = 0; i < 9; i++)
				{
					if (m_scene->GetActor<Player>()->GetUpgrade(i) >= m_scene->GetActor<Player>()->GetUpgradeLimit(i))
					{
						m_upgradeable[i] = false;
					}
					if (m_upgradeable[i]) numUpgradeable++;
				}
			} while (upgradeCount < 3 && upgradeCount < numUpgradeable);

			if (upgradeCount < 3)
			{
				if (upgradeCount < 2)
				{
					if (upgradeCount < 1)
					{
						m_upgradesSelected[0] = 11;
					}
					m_upgradesSelected[1] = 10;
				}
				m_upgradesSelected[2] = 9;
			}
			if (m_text.find("upgrade0") == m_text.end())
			{
				m_text.emplace("upgrade0", new Text(m_font, true));
				m_text["upgrade0"]->Create(RENDERER, GameData::upgradeText[m_upgradesSelected[0]], { 1, 1, 1 });
			}
			if (m_text.find("upgrade1") == m_text.end())
			{
				m_text.emplace("upgrade1", new Text(m_font, true));
				m_text["upgrade1"]->Create(RENDERER, GameData::upgradeText[m_upgradesSelected[1]], { 1, 1, 1 });
			}
			if (m_text.find("upgrade2") == m_text.end())
			{
				m_text.emplace("upgrade2", new Text(m_font, true));
				m_text["upgrade2"]->Create(RENDERER, GameData::upgradeText[m_upgradesSelected[2]], { 1, 1, 1 });
			}
			/*for (int i = 0; i < 9; i++)
			{
				std::cout << m_scene->GetActor<Player>()->GetUpgrade(i) << " ";
			}
			std::cout << std::endl;
			for (int i = 0; i < 9; i++)
			{
				std::cout << m_scene->GetActor<Player>()->GetUpgradeLimit(i) << " ";
			}
			std::cout << std::endl;*/
			m_state = eState::UpgradeSelection;
		}
		break;
	case eState::UpgradeSelection:
		if (m_scene->GetActor<Player>())
		{
			if (INPUT.GetKeyPressed(SDL_SCANCODE_RIGHT) && m_upgradeHover < 2) m_upgradeHover++;
			if (INPUT.GetKeyPressed(SDL_SCANCODE_LEFT) && m_upgradeHover > 0) m_upgradeHover--;
			if (INPUT.GetKeyPressed(SDL_SCANCODE_Z))
			{
				int temp = m_upgradesSelected[m_upgradeHover];
				switch (temp)
				{
				case 6:
					m_scene->GetActor<Player>()->Upgrade(temp);
					m_scene->GetActor<Player>()->SetMaxHP(5 * (m_scene->GetActor<Player>()->GetUpgrade(6) + 1));
					break;
				case 9:
					m_scene->GetActor<Player>()->SetHP(m_scene->GetActor<Player>()->GetHPMax());
					//std::cout << "HP Restore \n";
					break;
				case 10:
					m_score += 1000;
					//std::cout << "Score Up \n";
					break;
				case 11:
					m_scene->RemoveAll("Enemy");
					//std::cout << "Screen Clear \n";
					break;
				default:
					m_scene->GetActor<Player>()->Upgrade(temp);
					//std::cout << "Player Upgrade #" << temp << std::endl;
					break;
				}
				for (int i = 0; i < 3; i++)
				{
					m_upgradesSelected[i] = -1;
				}
				m_text.erase("upgrade0");
				m_text.erase("upgrade1");
				m_text.erase("upgrade2");
				m_state = eState::Game;
			}
		}
		break;
	case eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			{
				std::stringstream score;
				score << "Your Score " << m_score;
				if (m_text.find("finalScore") == m_text.end())
				{
					m_text.emplace("finalScore", new Text(m_font));
					m_text["finalScore"]->Create(RENDERER, score.str().c_str(), { 1, 1, 1 });
				}
				int seconds = (int)m_gameTime % 60;
				int minutes = (int)m_gameTime / 60;
				std::stringstream time;
				time << "Your Time " << minutes << " " << seconds;
				if (m_text.find("finalTime") == m_text.end())
				{
					m_text.emplace("finalTime", new Text(m_font));
					m_text["finalTime"]->Create(RENDERER, time.str().c_str(), { 1, 1, 1 });
				}

				std::ifstream input(m_recordFile);
				if (input.is_open())
				{
					while (!input.eof())
					{
						if (!input.fail())
						{
							input >> m_highscore;
							input >> m_hightime;
						}
					}
					input.close();
				}

				m_highscore = (m_score > m_highscore) ? m_score : m_highscore;
				m_hightime = (m_gameTime > m_hightime) ? m_gameTime : m_hightime;

				std::stringstream highscore;
				highscore << "Highscore " << m_highscore;
				if (m_text.find("highscore") == m_text.end())
				{
					m_text.emplace("highscore", new Text(m_font));
					m_text["highscore"]->Create(RENDERER, highscore.str().c_str(), { 1, 1, 1 });
				}
				std::stringstream hightime;
				seconds = (int)m_hightime % 60;
				minutes = (int)m_hightime / 60;
				hightime << "Highest Time " << minutes << " " << seconds;
				if (m_text.find("hightime") == m_text.end())
				{
					m_text.emplace("hightime", new Text(m_font));
					m_text["hightime"]->Create(RENDERER, hightime.str().c_str(), { 1, 1, 1 });
				}

				std::ofstream output(m_recordFile, std::ofstream::out | std::ofstream::trunc);
				if (output.is_open())
				{
					output << m_highscore << std::endl;
					output << m_hightime;
					output.close();
				}
				if (m_text.find("gameOver") == m_text.end())
				{
					m_text.emplace("gameOver", new Text(m_lgFont, true));
					m_text["gameOver"]->Create(RENDERER, "Game Over", { 1, 1, 1 });
				}
				if (m_text.find("gameRestart") == m_text.end())
				{
					m_text.emplace("gameRestart", new Text(m_font, true));
					m_text["gameRestart"]->Create(RENDERER, "Press Space to Restart", { 1, 1, 1 });
				}
			}
			m_scene->RemoveAll();
			PS.ClearParticles();
			m_state = eState::GameOver;
		}
		break;
	case eState::GameOver:
		if (INPUT.GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_text.erase("finalScore");
			m_text.erase("finalTime");
			m_text.erase("highscore");
			m_text.erase("hightime");
			m_text.erase("gameOver");
			m_text.erase("gameRestart");
			m_state = eState::StartGame;
		}
		break;
	default:
		break;
	}
	
	if (m_state == eState::Game || m_state == eState::PlayerDead)
	{
		m_engine->SetParticlesActive(true);
		m_scene->Update(dt);
	}
	else m_engine->SetParticlesActive(false);
}

void AndromedaDefense::Draw(Renderer& renderer)
{
	m_scene->Draw(renderer);

	switch (m_state)
	{
	case eState::Title:
		if (m_text.find("title") != m_text.end()) m_text["title"]->Draw(renderer, renderer.GetWidth() / 2, (int)(renderer.GetHeight() / 3));
		if (m_text.find("startTxt") != m_text.end()) m_text["startTxt"]->Draw(renderer, renderer.GetWidth() / 2, (int)(renderer.GetHeight() / 3) * 2);
		break;
	case eState::Game:
		if (m_text.find("timer") != m_text.end()) m_text["timer"]->Draw(renderer, renderer.GetWidth() / 2, 40);
		if (m_text.find("score") != m_text.end()) m_text["score"]->Draw(renderer, 40, 40);
		if (m_text.find("hp") != m_text.end()) m_text["hp"]->Draw(renderer, 40, 80);
		break;
	case eState::Pause:
		renderer.SetColor({ 0.0f, 0.0f, 0.0f, 0.5f });
		renderer.DrawRect(renderer.GetWidth() / 2, renderer.GetHeight() / 2, renderer.GetWidth(), renderer.GetHeight());
		if (m_text.find("pause") != m_text.end()) m_text["pause"]->Draw(renderer, renderer.GetWidth() / 2, (int)(renderer.GetHeight() / 3));
		break;
	case eState::UpgradeSelection:
		renderer.SetColor({ 0.0f, 0.0f, 0.0f, 0.5f });
		renderer.DrawRect(renderer.GetWidth() / 2, renderer.GetHeight() / 2, renderer.GetWidth(), renderer.GetHeight());
		renderer.SetColor({ 1, 1, 1 });
		renderer.DrawRect((renderer.GetWidth() / 4) * (m_upgradeHover + 1), renderer.GetHeight() / 2, 330, 730);
		renderer.SetColor({ 0, 0, 0 });
		renderer.DrawRect(renderer.GetWidth() / 4, renderer.GetHeight() / 2, 300, 700);
		renderer.DrawRect((renderer.GetWidth() / 4) * 2, renderer.GetHeight() / 2, 300, 700);
		renderer.DrawRect((renderer.GetWidth() / 4) * 3, renderer.GetHeight() / 2, 300, 700);
		renderer.SetColor({ 1, 1, 1 });
		if (m_text.find("upgrade0") != m_text.end()) m_text["upgrade0"]->Draw(renderer, renderer.GetWidth() / 4, (int)(renderer.GetHeight() / 2));
		if (m_text.find("upgrade1") != m_text.end()) m_text["upgrade1"]->Draw(renderer, (renderer.GetWidth() / 4) * 2, (int)(renderer.GetHeight() / 2));
		if (m_text.find("upgrade2") != m_text.end()) m_text["upgrade2"]->Draw(renderer, (renderer.GetWidth() / 4) * 3, (int)(renderer.GetHeight() / 2));
		break;
	case eState::GameOver:
		if (m_text.find("gameOver") != m_text.end()) m_text["gameOver"]->Draw(renderer, renderer.GetWidth() / 2, (int)(renderer.GetHeight() / 3));
		if (m_text.find("finalScore") != m_text.end()) m_text["finalScore"]->Draw(renderer, (renderer.GetWidth() / 2) - 300, (int)((renderer.GetHeight() / 3) + 100));
		if (m_text.find("finalTime") != m_text.end()) m_text["finalTime"]->Draw(renderer, (renderer.GetWidth() / 2) - 300, (int)((renderer.GetHeight() / 3) + 200));
		if (m_text.find("highscore") != m_text.end()) m_text["highscore"]->Draw(renderer, (renderer.GetWidth() / 2) + 100, (int)((renderer.GetHeight() / 3) + 100));
		if (m_text.find("hightime") != m_text.end()) m_text["hightime"]->Draw(renderer, (renderer.GetWidth() / 2) + 100, (int)((renderer.GetHeight() / 3) + 200));
		if (m_text.find("gameRestart") != m_text.end()) m_text["gameRestart"]->Draw(renderer, renderer.GetWidth() / 2, (int)((renderer.GetHeight() / 3) * 2));
		break;
	default:
		break;
	}
}

void AndromedaDefense::OnPlayerDeath()
{
	m_lives--;
	m_stateTimer = 3.0f;
	//m_state = (m_lives == 0) ? eState::GameOver : eState::PlayerDead;
	m_state = eState::PlayerDead;
}

void AndromedaDefense::AddExplosion(Vector2 position, Color color)
{
	for (int i = 0; i < random(1000, 3000); i++)
	{
		PS.AddParticle(Particle::Data{ position, randomOnUnitCircle() * randomf(1, 200), randomf(0.5f), color.ToInt(color.r), color.ToInt(color.g), color.ToInt(color.b), color.ToInt(color.a) });
	}
	for (int i = 0; i < random(1000, 2000); i++)
	{
		PS.AddParticle({position, randomOnUnitCircle() * randomf(1, 200), randomf(0.5f),  255, 130, 0, 255 });
	}
}

void AndromedaDefense::SpawnPlayer()
{
	Model* model = new Model{ GameData::playerShipPoints, Color{ 1, 0, 1 } };
	Transform transform{ {RENDERER.GetWidth() / 2, RENDERER.GetHeight() / 2}, 0, 3 };

	auto player = std::make_unique<Player>(1000, 7.5, transform, model);
	player->SetDamping(3.5f);
	player->SetRDamping(2.5f);
	player->SetDamage(1);
	player->SetMaxHP(5);
	player->SetTag("Player");
	m_scene->AddActor(std::move(player));
}

void AndromedaDefense::SpawnRammer()
{
	Model* model = new Model{ GameData::rammerShipPoints, Color{ 1, 0, 0 } };
	std::unique_ptr<Enemy> enemy{ nullptr };
	switch (random(4))
	{
	case 0:
		enemy = std::make_unique<Enemy>(250 * ((m_gamestage / 2) + 1), Transform{ { randomf(RENDERER.GetWidth()), 0.0f}, 0, 4}, model);
		break;
	case 1:
		enemy = std::make_unique<Enemy>(250 * ((m_gamestage / 2) + 1), Transform{ { (float)RENDERER.GetWidth(), randomf(RENDERER.GetHeight()) }, 0, 4 }, model);
		break;
	case 2:
		enemy = std::make_unique<Enemy>(250 * ((m_gamestage / 2) + 1), Transform{ { randomf(RENDERER.GetWidth()), (float)RENDERER.GetHeight() }, 0, 4 }, model);
		break;
	case 3:
		enemy = std::make_unique<Enemy>(250 * ((m_gamestage / 2) + 1), Transform{ { 0.0f, randomf(RENDERER.GetHeight()) }, 0, 4 }, model);
		break;
	default:
		enemy = std::make_unique<Enemy>(250 * ((m_gamestage / 2) + 1), Transform{ { RENDERER.GetWidth(), RENDERER.GetHeight() }, 0, 4 }, model);
		break;
	}
	enemy->SetDamping(3.5f);
	enemy->SetHP(m_gamestage / 2);
	enemy->SetDamage(((m_gamestage / 2) < 1) ? 1 : m_gamestage / 2);
	enemy->SetExpValue(m_scene->GetActor<Player>()->GetLevel());
	//enemy->SetExpValue(999);
	enemy->SetTag("Enemy");
	m_scene->AddActor(std::move(enemy));
}

void AndromedaDefense::SpawnShooter()
{
	Model* model = new Model{ GameData::shooterShipPoints, Color{ 1, 1, 0 } };
	std::unique_ptr<Shooter> enemy{ nullptr };
	switch (random(4))
	{
	case 0:
		enemy = std::make_unique<Shooter>(200 * ((m_gamestage / 2) + 1), Transform{ { randomf(RENDERER.GetWidth()), 0.0f}, 0, 3.5f }, model);
		break;
	case 1:
		enemy = std::make_unique<Shooter>(200 * ((m_gamestage / 2) + 1), Transform{ { (float)RENDERER.GetWidth(), randomf(RENDERER.GetHeight()) }, 0, 3.5f }, model);
		break;
	case 2:
		enemy = std::make_unique<Shooter>(200 * ((m_gamestage / 2) + 1), Transform{ { randomf(RENDERER.GetWidth()), (float)RENDERER.GetHeight() }, 0, 3.5f }, model);
		break;
	case 3:
		enemy = std::make_unique<Shooter>(200 * ((m_gamestage / 2) + 1), Transform{ { 0.0f, randomf(RENDERER.GetHeight()) }, 0, 3.5f }, model);
		break;
	default:
		enemy = std::make_unique<Shooter>(200 * ((m_gamestage / 2) + 1), Transform{ { RENDERER.GetWidth(), RENDERER.GetHeight() }, 0, 3.5f }, model);
		break;
	}
	enemy->SetDamping(3.5f);
	enemy->SetHP(m_gamestage / 2);
	enemy->SetDamage(m_gamestage / 2);

	enemy->SetFireTime(3.0f / (m_gamestage / 4.0f));
	enemy->SetFireRange(randomf(300, 600));
	enemy->SetBulletSpeed(randomf(100, 200) * (m_gamestage / 2.0f));

	enemy->SetExpValue(m_scene->GetActor<Player>()->GetLevel() * 2);
	enemy->SetTag("Enemy");
	m_scene->AddActor(std::move(enemy));
}

void AndromedaDefense::SpawnHealthPickup(Vector2 location)
{
	Model* model = new Model{ GameData::healthPickupPoints, Color{ 0, 1, 0 } };
	auto pickup = std::make_unique<Pickup>(Transform{ location, 0, 4 }, model);
	pickup->SetTag("Pickup");
	m_scene->AddActor(std::move(pickup));
}

void AndromedaDefense::SpawnPointPickup(Vector2 location)
{
	Model* model = new Model{ GameData::scorePickupPoints, Color{ 0.5f, 0.0f, 1.0f } };
	auto pickup = std::make_unique<PointPickup>(Transform{ location, 0, 4 }, model);
	pickup->SetTag("Pickup");
	m_scene->AddActor(std::move(pickup));
}
