#include "Bullet.h"
#include "Engine.h"

void Bullet::Update(float dt)
{
	Particle::Data data
	{
		m_transform.position,
		Vector2{1,0}.Rotate(randomf(Math::TwoPi)) * 50,
		randomf(0.05f, 0.25f),
		m_model->GetColor().ToInt(m_model->GetColor().r), 
		m_model->GetColor().ToInt(m_model->GetColor().g),
		m_model->GetColor().ToInt(m_model->GetColor().b),
		m_model->GetColor().ToInt(m_model->GetColor().a)
	};
	PS.AddParticle(data);

	m_velocity = Vector2{ m_speed, 0.0f }.Rotate(m_transform.rotation);
	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
	if (actor->GetTag() != m_tag && actor->GetTag() != "Pickup") m_destroyed = true;
}