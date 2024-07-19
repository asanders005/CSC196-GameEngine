#include "AndromedaDefense.h"
#include "Scene.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameData.h"
#include "Font.h"
#include "Text.h"

bool AndromedaDefense::Initialize()
{
	m_scene = new Scene();

	m_font = new Font();
	m_font->Load("pdark.ttf", 20);
	m_lgFont = new Font();
	m_lgFont->Load("pdark.ttf", 50);

	m_text.emplace("test", new Text(m_font));
	m_text["test"]->Create(RENDERER, "uwu", {1, 1, 1});

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
		if (m_engine->GetInput().GetKeyPressed(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	case eState::StartGame:
		m_score = 0;
		
		SpawnPlayer();

		m_level = 1;
		m_exp = 0;
		m_expBase = 10;
		m_expScale = 1.1f;

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

		if (m_exp >= (Math::Powf((float)(m_expBase * m_level), m_expScale)))
		{
			m_exp = 0;
			m_state = eState::LevelUp;
		}
		break;
	case eState::Pause:
		break;
	case eState::LevelUp:
		break;
	case eState::PlayerDead:
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
	
	m_scene->Update(dt);
}

void AndromedaDefense::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case eState::Title:
		m_text["title"]->Draw(RENDERER, RENDERER.GetWidth() / 2, RENDERER.GetHeight() / 2);
		break;
	case eState::GameOver:
		break;
	default:
		break;
	}
	m_scene->Draw(renderer);
}

void AndromedaDefense::SpawnPlayer()
{
	Model* model = new Model{ GameData::playerShipPoints, Color{ 1, 0, 1 } };
	Transform transform{ {RENDERER.GetWidth() / 2, RENDERER.GetHeight() / 2}, 0, 3 };

	Player* player = new Player(3000, 10, transform, model);
	player->SetDamping(3.5f);
	player->SetRDamping(2.5f);
	player->SetTag("Player");
	m_scene->AddActor(player);
}

void AndromedaDefense::SpawnRammer()
{
	Model* model = new Model{ GameData::rammerShipPoints, Color{ 1, 0, 0 } };
	Enemy* enemy = new Enemy(1500, Transform{ { RENDERER.GetWidth(), RENDERER.GetHeight() }, 0, 4 }, model);
	enemy->SetDamping(3.5f);
	enemy->SetTag("Enemy");
	m_scene->AddActor(enemy);
}