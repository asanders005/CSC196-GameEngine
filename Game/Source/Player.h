#pragma once
#include "Actor.h"

class Player : public Actor
{
public:
	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}
	Player(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Player(float speed, float rSpeed, const Transform& transform, Model* model) : Actor{ transform, model }, m_speed{ speed }, m_rSpeed{ rSpeed } {}

	void Update(float dt);

	void SetRDamping(float damping) { m_rDamping = damping; }

private:
	float m_speed = 0;
	float m_rSpeed = 0;
	float m_rAccel = 0;
	float m_rDamping = 0;

	float m_fireTimer = 0;
};