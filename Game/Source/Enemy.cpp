#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include <iostream>

void Enemy::Update(float dt)
{
	m_player = m_scene->GetActor<Player>();
	if (m_player)
	{
		Vector2 direction = m_player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalized() * m_speed * dt;
		//m_velocity = Vector2::Clamp(m_velocity, { -300, -300 }, { 300, 300 });
		m_transform.rotation = direction.Angle();
	}

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		m_hp -= actor->GetDamage();
		if (m_hp <= 0)
		{
			m_player->AddExp(m_expValue);
			m_destroyed = true;
		}
	}
}
