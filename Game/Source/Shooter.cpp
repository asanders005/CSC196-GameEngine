#include "Shooter.h"
#include "Player.h"
#include "Scene.h"
#include "Model.h"
#include "GameData.h"
#include "Bullet.h"
#include "Engine.h"
#include "AndromedaDefense.h"
#include "Random.h"
#include <iostream>

void Shooter::Update(float dt)
{
	m_player = m_scene->GetActor<Player>();
	m_fireTimer -= dt;
	if (m_player)
	{
		Vector2 direction = m_player->GetTransform().position - m_transform.position;
		m_transform.rotation = direction.Angle();
		if (direction.Length() > m_fireRange)
		{
			m_velocity += direction.Normalized() * m_speed * dt;
		}
		else if (m_fireTimer <= 0)
		{
			m_fireTimer = m_fireTime;

			Model* model = new Model{ GameData::playerBulletPoints, Color{ 1, 1, 0 } };
			Transform transform{ m_transform.position, m_transform.rotation };

			auto bullet = std::make_unique<Bullet>(m_bulletSpeed, transform, model);
			bullet->SetDamage(m_damage);
			bullet->SetLifespan(4);
			bullet->SetTag("Enemy");
			m_scene->AddActor(std::move(bullet));
		}
		//m_velocity = Vector2::Clamp(m_velocity, { -300, -300 }, { 300, 300 });
	}

	Actor::Update(dt);
}

void Shooter::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player")
	{
		m_hp -= actor->GetDamage();
		if (m_hp <= 0)
		{
			AndromedaDefense* game = dynamic_cast<AndromedaDefense*>(m_scene->GetGame());
			if (m_player && !dynamic_cast<Player*>(actor))
			{
				game->AddPoints(300);
				m_player->AddExp(m_expValue);
			}
			if (random(100) >= 95)
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
