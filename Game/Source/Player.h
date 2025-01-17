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

	int GetHP() const { return m_hp; }
	int GetHPMax() const { return m_maxHP; }
	void SetMaxHP(int hp) { m_maxHP = hp; Actor::SetHP(hp); }
	void AddHP(int hp) { m_hp = Math::Clamp(m_hp + hp, 0, m_maxHP); }

	void AddExp(int exp) { m_exp += exp; }
	int GetExp() const { return m_exp; }
	void ResetExp() { m_exp = 0; }

	int GetLevel() const { return m_level; }
	void LevelUp() { m_level++; }

	int GetUpgrade(int index) const { return m_upgrades[index]; }
	int GetUpgradeLimit(int index) const { return m_upgradeLimit[index]; }
	void Upgrade(int index) { m_upgrades[index]++; }

private:
	float m_speed = 0;
	float m_rSpeed = 0;
	float m_rAccel = 0;
	float m_rDamping = 0;

	float m_fireTimer = 0;
	float m_shieldTimer = 0;

	int m_maxHP = 0;

	/* Upgrades:
	0 - Fire Rate (5)
	1 - Bullet Count (4)
	2 - Bullet Speed (5)
	3 - Bullet Size (3)
	4 - Bullet Damage (3)
	5 - Shield (3)
	6 - HP (5)
	7 - Speed (3)
	8 - Turn Speed (3) */
	int m_upgrades[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int m_upgradeLimit[9] = { 5, 4, 5, 3, 3, 3, 5, 3, 3 };

	int m_level = 1;
	int m_exp = 0;

	float m_iTime = 0;
};