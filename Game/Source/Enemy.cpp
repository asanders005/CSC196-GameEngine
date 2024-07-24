#include "Enemy.h"
#include "Player.h"
#include "Scene.h"
#include "Engine.h"
#include "AndromedaDefense.h"
#include "Random.h"
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
			AndromedaDefense* game = dynamic_cast<AndromedaDefense*>(m_scene->GetGame());
			if (m_player && !dynamic_cast<Player*>(actor))
			{
				game->AddPoints(100);
				m_player->AddExp(m_expValue);
			}
			if (random(100) == 95)
			{
				if (random(2) == 1)
				{
					game->SpawnHealthPickup(m_transform.position);
				}
				else
				{
					game->SpawnPointPickup(m_transform.position);
				}
			}
			AUDIO.PlaySound("ShipExplode.wav");
			game->AddExplosion(m_transform.position, m_model->GetColor());
			m_destroyed = true;
		}
	}
}
