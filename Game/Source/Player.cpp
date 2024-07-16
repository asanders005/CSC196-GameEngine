#include "Player.h"
#include "Engine.h"
#include "Mathutils.h"
#include "Bullet.h"
#include "Scene.h"

void Player::Update(float dt)
{
	// movement
	float thrust = 0;
	if (INPUT.GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
	if (INPUT.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;
	if (INPUT.GetKeyDown(SDL_SCANCODE_LEFT)) m_rAccel -= m_rSpeed;
	if (INPUT.GetKeyDown(SDL_SCANCODE_RIGHT)) m_rAccel += m_rSpeed;

	m_rAccel = Math::Clamp(m_rAccel, -450.0f, 450.0f);
	m_transform.rotation += Math::DegToRad(m_rAccel) * dt;
	m_rAccel *= 1.0f / (1.0f + m_rDamping * dt);

	Vector2 acceleration = Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);
	m_velocity += acceleration * dt;
	//m_velocity.x = Math::Clamp(m_velocity.x, -250.0f, 250.0f);
	
	m_transform.position = Vector2::Wrap(m_transform.position, { (float)RENDERER.GetWidth(), (float)RENDERER.GetHeight() });
	
	// fire
	m_fireTimer -= dt;
	if (INPUT.GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0)
	{
		m_fireTimer = 0.5f;

		std::vector<Vector2> points;
		points.push_back(Vector2{ 5, 0 });
		points.push_back(Vector2{ -5, -5 });
		points.push_back(Vector2{ -5, 5 });
		points.push_back(Vector2{ 5, 0 });
		std::vector<std::vector<Vector2>>shapes;
		shapes.push_back(points);

		// actor
		Model* model = new Model{ shapes, Color{ 1, 0, 0 } };
		Transform transform{ m_transform.position, m_transform.rotation };

		Bullet* bullet = new Bullet(500, transform, model);
		bullet->SetLifespan(1);
		m_scene->AddActor(bullet);
	}

	Actor::Update(dt);
}