#include "Engine.h"
#include "Player.h"
#include "Scene.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <time.h>

int main(int argc, char* argv[])
{
	g_engine.Initialize();
	// create systems
	

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	Time etime;

	Scene* scene = new Scene();

	std::vector<Particle> particles;

	/*AUDIO.AddSound("bass.wav");
	AUDIO.AddSound("clap.wav");
	AUDIO.AddSound("close-hat.wav");
	AUDIO.AddSound("cowbell.wav");
	AUDIO.AddSound("open-hat.wav");
	AUDIO.AddSound("snare.wav");*/
		
	float offset = 0;

	std::vector<std::vector<Vector2>> shapes;
	std::vector<Vector2> points;
	points.push_back(Vector2{ 11, 0 });
	points.push_back(Vector2{ 8, 1 });
	points.push_back(Vector2{ -3, 7 });
	points.push_back(Vector2{ -4, 6 });
	points.push_back(Vector2{ -2, 2 });
	points.push_back(Vector2{ -9, 5 });
	points.push_back(Vector2{ -9, 4 });
	points.push_back(Vector2{ -8, 2 });
	points.push_back(Vector2{ -11, 4 });
	points.push_back(Vector2{ -11, 3 });
	points.push_back(Vector2{ -9, 1 });
	points.push_back(Vector2{ -9, -1 });
	points.push_back(Vector2{ -11, -3 });
	points.push_back(Vector2{ -11, -4 });
	points.push_back(Vector2{ -8, -2 });
	points.push_back(Vector2{ -9, -4 });
	points.push_back(Vector2{ -9, -5 });
	points.push_back(Vector2{ -2, -2 });
	points.push_back(Vector2{ -4, -6 });
	points.push_back(Vector2{ -3, -7 });
	points.push_back(Vector2{ 8, -1 });
	points.push_back(Vector2{ 11, 0 });
	shapes.push_back(points);
	points.clear();
	points.push_back(Vector2{ 9, 0 });
	points.push_back(Vector2{ 6, 1 });
	points.push_back(Vector2{ 6, -1 });
	points.push_back(Vector2{ 9, 0 });
	shapes.push_back(points);
	points.clear();
	points.push_back(Vector2{ -2, 0 });
	points.push_back(Vector2{ 3, 0 });
	points.push_back(Vector2{ 4, 1 });
	points.push_back(Vector2{ -1, 2 });
	points.push_back(Vector2{ -2, 1 });
	points.push_back(Vector2{ -2, -1 });
	points.push_back(Vector2{ -1, -2 });
	points.push_back(Vector2{ 4, -1 });
	points.push_back(Vector2{ 3, 0 });
	shapes.push_back(points);
	points.clear();
	points.push_back(Vector2{ -7, 1 });
	points.push_back(Vector2{ -4, 0 });
	points.push_back(Vector2{ -7, -1 });
	points.push_back(Vector2{ -8, -1 });
	points.push_back(Vector2{ -7, -2 });
	points.push_back(Vector2{ -3, -1 });
	points.push_back(Vector2{ -3, 1 });
	points.push_back(Vector2{ -7, 2 });
	points.push_back(Vector2{ -8, 1 });
	points.push_back(Vector2{ -7, 1 });
	points.push_back(Vector2{ -8, 0 });
	points.push_back(Vector2{ -7, -1 });
	shapes.push_back(points);
	points.clear();
	Model* model = new Model{ shapes, Color{ 1, 0, 1 } };
	Transform transform{ {RENDERER.GetWidth() / 2, RENDERER.GetHeight() / 2}, 0, 3 };
	
	Player* player = new Player(3000, 5, transform, model);
	player->SetDamping(3.5f);
	player->SetRDamping(2.5f);
	player->SetTag("Player");
	scene->AddActor(player);

	Model* eModel = new Model{ shapes, Color{ 1, 1, 0 } };
	Enemy* enemy = new Enemy(1500, Transform{ { RENDERER.GetWidth(), RENDERER.GetHeight() }, 0, 2}, eModel);
	enemy->SetDamping(3.5f);
	enemy->SetTag("Enemy");
	scene->AddActor(enemy);

	srand(time(0));
	
	float spawnTimer = 2;

	// main
	bool quit = false;
	while (!quit)
	{
		etime.Tick();
		//std::cout << time.GetTime() << std::endl;
		
		// INPUT
		audio->update();

		INPUT.Update();

		if (INPUT.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		/*if (INPUT.GetKeyPressed(SDL_SCANCODE_W)) AUDIO.PlaySound("cowbell.wav");
		if (INPUT.GetKeyPressed(SDL_SCANCODE_E)) AUDIO.PlaySound("open-hat.wav");
		if (INPUT.GetKeyPressed(SDL_SCANCODE_R)) AUDIO.PlaySound("close-hat.wav");
		if (INPUT.GetKeyPressed(SDL_SCANCODE_U)) AUDIO.PlaySound("snare.wav");
		if (INPUT.GetKeyPressed(SDL_SCANCODE_I)) AUDIO.PlaySound("bass.wav");
		if (INPUT.GetKeyPressed(SDL_SCANCODE_O)) AUDIO.PlaySound("clap.wav");*/
		
		// UPDATE
		spawnTimer -= etime.GetDeltaTime();
		if (spawnTimer <= 0)
		{
			Enemy* enemy = new Enemy(1500, Transform{ { RENDERER.GetWidth(), RENDERER.GetHeight() }, 0, 2 }, eModel);
			enemy->SetDamping(3.5f);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);
			spawnTimer = 2;
		}

		scene->Update(etime.GetDeltaTime());

		Vector2 mousePosition = INPUT.GetMousePosition();
		if (INPUT.GetMouseButtonPressed(0)) 
		{
			uint8_t r{ (uint8_t)random(256) }, g{ (uint8_t)random(256) }, b{ (uint8_t)random(256) }, a{ (uint8_t)random(256) };
			for (int i = 0; i < random(1000, 5000); i++) {
				particles.push_back(Particle{ mousePosition, randomOnUnitCircle() * randomf(300), randomf(1), r, g, b, a});
			}
		}

		for (Particle& p : particles)
		{
			p.Update(etime.GetDeltaTime());
			/*if (p.position.x > 800) p.position.x = 0;
			else if (p.position.x < 0) p.position.x = 800;*/
		}

		// DRAW
		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();
		
		RENDERER.SetColor(255, 255, 255, 0);
		float radius = 100;
		offset += (90 * etime.GetDeltaTime());
		/*for (float angle = 0; angle < 360; angle += 360 / 90)
		{
			Vector2 v{ Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius, Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius };
			renderer.SetColor((uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256));
			renderer.DrawRect(400 - v.x, 300 - v.y, 5.0f, 5.0f);
		}*/

		for (Particle p : particles)
		{
			p.Draw(RENDERER);
		}

		scene->Draw(RENDERER);

		RENDERER.EndFrame();
	}

	return 0;
}