#pragma once
#include "Particle.h"
#include <list>
#include <vector>
#include <string>
#include <memory>

class Renderer;
class Actor;
class Game;

class Scene
{
public:
	//Scene() = default;
	Scene(Game* game) : m_game{ game } {}

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(std::unique_ptr<Actor> actor);
	//void AddParticle(Vector2 position, Vector2 velocity, float lifespan, Color color);
	//void ClearParticles();

	void RemoveAll();
	void RemoveAll(std::string tag);

	template<typename T>
	T* GetActor();

	Game* GetGame() { return m_game; }
	
private:
	std::list<std::unique_ptr<Actor>> m_actors;
	//std::vector<Particle> m_particles;

	Game* m_game{ nullptr };
};

template<typename T>
T* Scene::GetActor()
{
	for (auto& actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor.get());
		if (result) return result;
	}

	return nullptr;
}