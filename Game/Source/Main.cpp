#include "Renderer.h"
#include "Vector2.h"
#include "Input.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "Mathutils.h"
#include "Model.h"

#include <SDL.h>
#include <fmod.hpp>
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

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);

	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

	Time etime;

	std::vector<Particle> particles;

	FMOD::Sound* sound = nullptr;
	std::vector<FMOD::Sound*> sounds;

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);
	
	float offset = 0;

	std::vector<Vector2> points;
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ 5, -5 });
	points.push_back(Vector2{ 0, 5 });
	points.push_back(Vector2{ -5, -5 });
	Model model{ points, Color{ 1, 0, 1, 1} };
	Vector2 position{ 400, 300 };
	float rotation = 0;

	srand(time(0));
		
	// main
	bool quit = false;
	while (!quit)
	{
		etime.Tick();
		//std::cout << time.GetTime() << std::endl;
		
		// INPUT
		audio->update();

		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		if (input.GetKeyPressed(SDL_SCANCODE_W)) audio->playSound(sounds[0], 0, false, nullptr);
		if (input.GetKeyPressed(SDL_SCANCODE_E)) audio->playSound(sounds[1], 0, false, nullptr);
		if (input.GetKeyPressed(SDL_SCANCODE_R)) audio->playSound(sounds[2], 0, false, nullptr);
		if (input.GetKeyPressed(SDL_SCANCODE_U)) audio->playSound(sounds[3], 0, false, nullptr);
		if (input.GetKeyPressed(SDL_SCANCODE_I)) audio->playSound(sounds[4], 0, false, nullptr);
		if (input.GetKeyPressed(SDL_SCANCODE_O)) audio->playSound(sounds[5], 0, false, nullptr);

		Vector2 velocity{ 0, 0 };
		if (input.GetKeyDown(SDL_SCANCODE_LEFT)) velocity.x = -100;
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT)) velocity.x = 100;
		if (input.GetKeyDown(SDL_SCANCODE_UP)) velocity.y = -100;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN)) velocity.y = 100;

		position = position + (velocity * etime.GetDeltaTime());
		rotation = velocity.Angle();
		
		// UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonPressed(0)) 
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
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		
		renderer.SetColor(255, 255, 255, 0);
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
			p.Draw(renderer);
		}

		model.Draw(renderer, position, rotation, 10);

		renderer.EndFrame();
	}

	return 0;
}