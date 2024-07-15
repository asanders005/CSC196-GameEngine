#include "Player.h"
#include "Engine.h"
#include "Mathutils.h"

void Player::Update(float dt)
{
	float thrust = 0;
	if (INPUT.GetKeyDown(SDL_SCANCODE_UP)) thrust = m_speed;
	if (INPUT.GetKeyDown(SDL_SCANCODE_DOWN)) thrust = -m_speed;
	if (INPUT.GetKeyDown(SDL_SCANCODE_LEFT)) m_rSpeed -= 2;
	if (INPUT.GetKeyDown(SDL_SCANCODE_RIGHT)) m_rSpeed += 2;

	m_rSpeed = Math::Clamp(m_rSpeed, -450.0f, 450.0f);
	m_transform.rotation += Math::DegToRad(m_rSpeed) * dt;
	m_rSpeed *= 1.0f / (1.0f + m_rDamping * dt);

	m_velocity += Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);
	//m_velocity.x = Math::Clamp(m_velocity.x, -250.0f, 250.0f);
	
	m_transform.position = Vector2::Wrap(m_transform.position, { (float)RENDERER.GetWidth(), (float)RENDERER.GetHeight() });
	
	Actor::Update(dt);
}