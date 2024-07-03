#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"

#include <SDL.h>
#include <iostream>
#include <vector>
#include <time.h>

int main(int argc, char* argv[])
{
	// create systems
	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Game Engine", 800, 600);
	
	Input input;
	input.Initialize();

	Time etime;

	std::vector<Particle> particles;

	srand(time(0));
		
	// main
	bool quit = false;
	while (!quit)
	{
		etime.Tick();
		//std::cout << time.GetTime() << std::endl;
		
		// INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}
		
		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonPressed(0)) 
		{
			uint8_t r{ (uint8_t)random(256) }, g{ (uint8_t)random(256) }, b{ (uint8_t)random(256) }, a{ (uint8_t)random(256) };
			for (int i = 0; i < random(1000, 5000); i++) {
				particles.push_back(Particle{ mousePosition, { randomf(-300, 300) , randomf(-300, 300) }, randomf(1), r, g, b, a });
			}
		}

		for (Particle& p : particles)
		{
			p.Update(etime.GetDeltaTime());
			/*if (p.position.x > 800) p.position.x = 0;
			else if (p.position.x < 0) p.position.x = 800;*/
		}

		// DRAW
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		
		for (Particle p : particles)
		{
			renderer.SetColor(p.r, p.g, p.b, p.a);
			p.Draw(renderer);
		}

		renderer.EndFrame();
	}

	return 0;
}