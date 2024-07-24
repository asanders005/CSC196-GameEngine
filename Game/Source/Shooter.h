#pragma once
#include "Enemy.h"

class Player;

class Shooter : public Enemy
{
public:
	Shooter() = default;
	Shooter(const Transform& transform) : Enemy{ transform } {}
	Shooter(const Transform& transform, Model* model) : Enemy{ transform, model } {}
	Shooter(float speed, const Transform& transform, Model* model) : Enemy{ transform, model }, m_speed{ speed } {}

	virtual void Update(float dt) override;

	virtual void OnCollision(Actor* actor) override;

	void SetFireTime(float time) { m_fireTime = time; m_fireTimer = m_fireTime; }
	void SetFireRange(float range) { m_fireRange = range; }
	void SetBulletSpeed(float speed) { m_bulletSpeed = speed; }

	void SetExpValue(int expV) { m_expValue = expV; }

private:
	float m_fireTime = 0;
	float m_fireTimer = 0;
	float m_fireRange = 0;
	float m_bulletSpeed = 0;

	float m_speed = 0;

	int m_expValue = 0;

	Player* m_player{ nullptr };
};