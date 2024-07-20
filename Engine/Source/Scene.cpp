#include "Scene.h"
#include "Actor.h"
#include "Model.h"

void Scene::Update(float dt)
{
	for (Actor* actor : m_actors)
	{
		actor->Update(dt);
	}

	/*auto iter = m_actors.begin();
	while (iter != m_actors.end())
	{
		iter = ((*iter)->m_destroyed) ? m_actors.erase(iter) : ++iter;
	}*/

	// The std::remove_if algorithm reorders the elements in the range [m_actors.begin(), m_actors.end()]
	// such that the elements that satisfy the predicate (i.e., those that should be removed) are moved
	// to the end of the range. The algorithm returns an iterator to the beginning of the "removed" range,
	// which is the new logical end of the container.
	// m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [](Actor* actor) { return actor->m_destroyed; }), m_actors.end());
	std::erase_if(m_actors, [](Actor* actor) { return actor->m_destroyed; });
	
	//collision
	for (Actor* actor1 : m_actors)
	{
		for (Actor* actor2 : m_actors)
		{
			if (actor1 == actor2) continue;

			Vector2 direction = actor1->GetTransform().position - actor2->GetTransform().position;
			float distance = direction.Length();
			float radius = (actor1->m_model->GetRadius() * actor1->m_transform.scale) + (actor2->m_model->GetRadius() * actor2->m_transform.scale);

			if (distance <= radius)
			{
				actor1->OnCollision(actor2);
				actor2->OnCollision(actor1);
			}
		}
	}
}

void Scene::Draw(Renderer& renderer)
{
	for (Actor* actor : m_actors)
	{
		actor->Draw(renderer);
	}
}

void Scene::AddActor(Actor* actor)
{
	actor->m_scene = this;
	m_actors.push_back(actor);
}

void Scene::EraseAll(std::string tag)
{
	m_actors.erase(std::remove_if(m_actors.begin(), m_actors.end(), [&](Actor* actor) { return actor->GetTag() == tag; }), m_actors.end());
}
