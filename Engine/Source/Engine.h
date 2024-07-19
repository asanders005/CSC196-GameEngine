#pragma once
#include "Audio.h"
#include "Input.h"
#include "Renderer.h"

#include "ETime.h"

#include "Mathutils.h"
#include "Random.h"
#include "Vector2.h"

#include "Model.h"
#include "Particle.h"
#include "Transform.h"


#include <SDL.h>

#define RENDERER g_engine.GetRenderer()
#define INPUT g_engine.GetInput()
#define AUDIO g_engine.GetAudio()
#define TIME g_engine.GetTime()

class Engine
{
public:
	Engine() = default;
	~Engine() = default;

	bool Initialize();
	void Shutdown();

	void Update();

	Renderer& GetRenderer() { return *m_renderer; }
	Input& GetInput() { return *m_input; }
	Audio& GetAudio() { return *m_audio; }

	Time& GetTime() { return *m_time; }

	bool IsQuit() { return quit; }

private:
	bool quit{ false };

	Time* m_time{ nullptr };

	Renderer* m_renderer{ nullptr };
	Input* m_input{ nullptr };
	Audio* m_audio{ nullptr };
};

extern Engine g_engine;