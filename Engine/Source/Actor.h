#pragma once
#include "Transform.h"
#include "Model.h"
#include <string>

class Scene;

class Actor
{
public:
	Actor() = default;
	Actor(const Transform& transform) : m_transform{transform} {}
	Actor(const Transform& transform, Model* model) : m_transform{ transform }, m_model { model } {}
	
	virtual void Update(float dt);
	virtual void Draw(class Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifespan(float lifespan) { m_lifespan = lifespan; }

	const Transform& GetTransform() { return m_transform; }
	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	virtual void OnCollision(Actor* actor) = 0;
	float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }

	virtual void SetHP(int hp) { m_hp = hp; }

	void SetDamage(int damage) { m_damage = damage; }
	int GetDamage() const { return m_damage; }

	friend class Scene;

protected:
	std::string m_tag;
	int m_hp = 0;
	bool m_destroyed = false;
	float m_lifespan = -1;

	Transform m_transform;
	Vector2 m_velocity{ 0, 0 };
	float m_damping = 0;

	int m_damage = 0;

	Model* m_model{ nullptr };
	Scene* m_scene{ nullptr };
};