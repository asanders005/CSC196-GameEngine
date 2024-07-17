#include "Enemy.h"
#include "Player.h"
#include "Scene.h"

void Enemy::Update(float dt)
{
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		Vector2 direction = player->GetTransform().position - m_transform.position;
		m_velocity += direction.Normalized() * m_speed * dt;
		//m_velocity = Vector2::Clamp(m_velocity, { -300, -300 }, { 300, 300 });
		m_transform.rotation = direction.Angle();
	}

	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* actor)
{
	if (actor->GetTag() == "Player") m_destroyed = true;
}
