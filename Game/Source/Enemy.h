#pragma once
#include "Actor.h"

class Player;

class Enemy : public Actor
{
public:
	Enemy() = default;
	Enemy(const Transform& transform) : Actor{ transform } {}
	Enemy(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Enemy(float speed, const Transform& transform, Model* model) : Actor{ transform, model }, m_speed{ speed } {}

	virtual void Update(float dt);

	virtual void OnCollision(Actor* actor);

	void SetExpValue(int expV) { m_expValue = expV; }

private:
	float m_speed = 0;
	
	float m_fireTimer = 0;

	int m_expValue = 0;

	Player* m_player{ nullptr };
};