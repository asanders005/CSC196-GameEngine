#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Player(float speed, const Transform& transform, Model* model) : Actor{ transform, model }, m_speed{ speed } {}

	void Update(float dt);

	void SetRDamping(float damping) { m_rDamping = damping; }

private:
	float m_speed = 0;
	float m_rSpeed = 0;
	float m_rDamping = 0;
};