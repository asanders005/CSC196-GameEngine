#pragma once
#include "Pickup.h"

class PointPickup : public Pickup
{
public:
	PointPickup() = default;
	PointPickup(const Transform& transform) : Pickup{ transform } {}
	PointPickup(const Transform& transform, Model* model) : Pickup{ transform, model } {}

	void OnCollision(Actor* actor) override;

protected:

};