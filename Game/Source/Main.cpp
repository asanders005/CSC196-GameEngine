#include "Engine.h"
#include "AndromedaDefense.h"

#include <iostream>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	AndromedaDefense* game = new AndromedaDefense(&g_engine);
	game->Initialize();

	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		game->Update(TIME.GetDeltaTime());

		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();

		PS.Draw(RENDERER);
		game->Draw(RENDERER);

		RENDERER.EndFrame();
	}

	g_engine.Shutdown();

	return 0;
}

/*
	Scene* scene = new Scene();

	std::vector<Particle> particles;
		
	float offset = 0;

	srand(time(0));
	
	float spawnTimer = 2;

	// main
	while (!g_engine.IsQuit())
	{
		g_engine.Update();
		
		// UPDATE
		spawnTimer -= TIME.GetDeltaTime();
		if (spawnTimer <= 0)
		{
			Enemy* enemy = new Enemy(1500, Transform{ { RENDERER.GetWidth(), RENDERER.GetHeight() }, 0, 2 }, eModel);
			enemy->SetDamping(3.5f);
			enemy->SetTag("Enemy");
			scene->AddActor(enemy);
			spawnTimer = 2;
		}

		scene->Update(TIME.GetDeltaTime());

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
			p.Update(TIME.GetDeltaTime());
		}

		// DRAW
		RENDERER.SetColor(0, 0, 0, 0);
		RENDERER.BeginFrame();
		
		RENDERER.SetColor(255, 255, 255, 0);
		
		for (Particle p : particles)
		{
			p.Draw(RENDERER);
		}

		scene->Draw(RENDERER);

		RENDERER.EndFrame();
	}

	return 0;
}
*/