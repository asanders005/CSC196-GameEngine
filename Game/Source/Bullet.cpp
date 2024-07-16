#include "Bullet.h"

void Bullet::Update(float dt)
{
	m_velocity = Vector2{ m_speed, 0.0f }.Rotate(m_transform.rotation);
	Actor::Update(dt);
}