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

	void OnCollision(Actor* actor);

private:
	float m_speed = 0;
	float m_rSpeed = 0;
	float m_rAccel = 0;
	float m_rDamping = 0;

	float m_fireTimer = 0;

	/* Upgrades:
	0 - Bullet Count
	1 - Fire Rate
	2 - Bullet Speed
	3 - Bullet Damage
	4 - Jet Size
	5 - Jet Damage
	6 - Shield
	7 - HP
	8 - Speed
	9 - Turn Speed */
	int m_upgrades[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
};