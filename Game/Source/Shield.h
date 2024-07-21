#pragma once
#include "Actor.h"

class Shield : public Actor
{
public:
	Shield() = default;
	Shield(const Transform& transform) : Actor{ transform } {}
	Shield(const Transform& transform, Model* model) : Actor{ transform, model } {}
	Shield(Actor* parent, const Transform& transform, Model* model) : Actor{ transform, model }, m_parent{ parent } {}

	void Update(float dt);

	virtual void OnCollision(Actor* actor);

private:
	Actor* m_parent{ nullptr };
};