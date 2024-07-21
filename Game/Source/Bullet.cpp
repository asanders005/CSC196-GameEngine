#include "Bullet.h"

void Bullet::Update(float dt)
{
	m_velocity = Vector2{ m_speed, 0.0f }.Rotate(m_transform.rotation);
	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
	if (actor->GetTag() != m_tag) m_destroyed = true;
}