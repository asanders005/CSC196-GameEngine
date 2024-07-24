#include "Engine.h"

Engine g_engine;

bool Engine::Initialize()
{
	m_renderer = std::make_unique<Renderer>();
	m_input = std::make_unique<Input>();
	m_audio = std::make_unique<Audio>();

	m_particleSystem = std::make_unique<ParticleSystem>();

	m_renderer->Initialize();
	m_renderer->CreateWindow("Andromeda Defense", 1500, 900);
	m_input->Initialize();
	m_audio->Initialize();

	m_time = std::make_unique<Time>();

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
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LALT && event.key.keysym.sym == SDLK_F4) quit = true;
	}

	m_time->Tick();

	m_input->Update();
	m_audio->Update();
	if (m_particlesActive) m_particleSystem->Update(m_time->GetDeltaTime());
}
