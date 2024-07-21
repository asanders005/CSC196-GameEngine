#pragma once
#include "Text.h"
#include <map>

class Engine;
class Renderer;
class Scene;
class Font;

class Game
{
public:
	Game() = default;
	Game(Engine* engine) : m_engine{ engine } {}

	virtual bool Initialize() = 0;
	virtual void Shutdown() = 0;

	virtual void Update(float dt) = 0;
	virtual void Draw(Renderer& renderer) = 0;

	int GetScore() const { return m_score; }
	void AddPoints(int points) { m_score += points; }

protected:
	int m_score = 0;

	Font* m_font{ nullptr };
	Font* m_lgFont{ nullptr };
	Font* m_altFont{ nullptr };
	std::map<std::string, Text*> m_text;

	Engine* m_engine{ nullptr };
	Scene* m_scene{ nullptr };
};