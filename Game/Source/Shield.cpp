#include "Shield.h"

void Shield::Update(float dt)
{
	m_transform = m_parent->GetTransform();
	Actor::Update(dt);
}

void Shield::OnCollision(Actor* actor)
{

}