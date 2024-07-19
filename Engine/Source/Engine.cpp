#include "Engine.h"

Engine g_engine;

bool Engine::Initialize()
{
	m_renderer = new Renderer();
	m_input = new Input();
	m_audio = new Audio();

	m_renderer->Initialize();
	m_renderer->CreateWindow("Game Engine", 1500, 900);
	m_input->Initialize();
	m_audio->Initialize();

	m_time = new Time();

    return true;
}

void Engine::Shutdown()
{
	m_renderer->Shutdown();
	m_input->Shutdown();
	m_audio->Shutdown();
}

void Engine::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)	quit = true;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) quit = true;
	}

	m_time->Tick();

	m_input->Update();
	m_audio->Update();
}
