#include "Player.h"
#include "Engine.h"
#include "Mathutils.h"
#include "Bullet.h"
#include "Shield.h"
#include "Scene.h"
#include "GameData.h"
#include <iostream>

void Player::Update(float dt)
{
	m_iTime -= dt;

	// movement
	float thrust = 0;
	if (INPUT.GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed * ((m_upgrades[7] / 2.0f) + 1.0f);
	if (INPUT.GetKeyDown(SDL_SCANCODE_LEFT)) m_rAccel -= m_rSpeed * ((m_upgrades[8] / 2.0f) + 1.0f);
	if (INPUT.GetKeyDown(SDL_SCANCODE_RIGHT)) m_rAccel += m_rSpeed * ((m_upgrades[8] / 2.0f) + 1.0f);

	m_rAccel = Math::Clamp(m_rAccel, -450.0f, 450.0f);
	m_transform.rotation += Math::DegToRad(m_rAccel) * dt;
	m_rAccel *= 1.0f / (1.0f + m_rDamping * dt);

	Vector2 acceleration = Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);
	m_velocity += acceleration * dt;
	//m_velocity.x = Math::Clamp(m_velocity.x, -250.0f, 250.0f);
	
	m_transform.position = Vector2::Wrap(m_transform.position, { (float)RENDERER.GetWidth(), (float)RENDERER.GetHeight() });
	
	// fire
	m_fireTimer -= dt;
	if (INPUT.GetKeyDown(SDL_SCANCODE_Z) && m_fireTimer <= 0)
	{
		m_fireTimer = 0.5f / (m_upgrades[0] + 1);

		// actor
		for (int i = 0; i < m_upgrades[1] + 1; i++)
		{
			Model* model = new Model{ GameData::playerBulletPoints, Color{ 0.0f, 0.5f, 1.0f } };
			float bulletAngle = Math::DegToRad((9.0f * m_upgrades[1]) - (9.0f * i)) - Math::DegToRad((9.0f * m_upgrades[1]) * 0.5f);
			Transform transform{ m_transform.position, m_transform.rotation + bulletAngle, (float)((m_upgrades[3] / 2.0f) + 1.0f)};

			Bullet* bullet = new Bullet((500 * ((m_upgrades[2] / 2.0f) + 1.0f)), transform, model);
			bullet->SetDamage(m_upgrades[4] + 1);
			bullet->SetLifespan(1);
			bullet->SetTag("Player");
			m_scene->AddActor(bullet);
		}
	}

	m_shieldTimer -= dt;
	if (INPUT.GetKeyDown(SDL_SCANCODE_X) && m_shieldTimer <= 0)
	{
		m_shieldTimer = 5.0f / (m_upgrades[5] + 1);

		Model* model = new Model{ GameData::playerShieldPoints, Color{ 0.0f, 0.5f, 1.0f } };
		Transform transform{ m_transform.position, m_transform.rotation, m_transform.scale };

		Shield* shield = new Shield(this, transform, model);
		shield->SetDamage(m_upgrades[4] + 1);
		shield->SetLifespan(0.25f);
		shield->SetTag("Player");
		m_scene->AddActor(shield);
	}

	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Enemy" && m_iTime <= 0)
	{
		m_iTime = 0.5f;
		m_hp -= actor->GetDamage();
		if (m_hp <= 0) m_destroyed = true;
	}
}