#include "Scene.h"
#include "Actor.h"
#include "Model.h"

void Scene::Update(float dt)
{
	for (auto& actor : m_actors)
	{
		actor->Update(dt);
	}
	/*for (Particle p : m_particles)
	{
		p.Update(dt);
	}*/
	
	//collision
	for (auto& actor1 : m_actors)
	{
		for (auto& actor2 : m_actors)
		{
			if (actor1 == actor2 || (actor1->m_destroyed || actor2->m_destroyed)) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();
			float radius = actor1->GetRadius() + actor2->GetRadius();

			if (distance <= radius)
			{
				actor1->OnCollision(actor2.get());
				actor2->OnCollision(actor1.get());
			}
		}
	}
	std::erase_if(m_actors, [](auto& actor) { return actor->m_destroyed; });
}

void Scene::Draw(Renderer& renderer)
{
	for (auto& actor : m_actors)
	{
		actor->Draw(renderer);
	}
	/*for (Particle p : m_particles)
	{
		p.Draw(renderer);
	}*/
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	actor->m_scene = this;
	m_actors.push_back(std::move(actor));
}

//void Scene::AddParticle(Vector2 position, Vector2 velocity, float lifespan, Color color)
//{
//	m_particles.push_back(Particle{ position, velocity, lifespan, color.ToInt(color.r), color.ToInt(color.g), color.ToInt(color.b) });
//}
//
//void Scene::ClearParticles()
//{
//	m_particles.clear();
//}

void Scene::RemoveAll()
{
	m_actors.clear();
}

void Scene::RemoveAll(std::string tag)
{
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [&](auto& actor) { return actor->GetTag() == tag; }), m_actors.end());
}
