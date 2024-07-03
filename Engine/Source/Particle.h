#pragma once
#include "Vector2.h"
#include "Renderer.h"

struct Particle
{
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	float lifespan = 0;

	uint8_t r{ 0 }, g{ 0 }, b{ 0 }, a{ 0 };

	Particle() = default;
	Particle(Vector2 position, Vector2 velocity) : position{ position }, velocity{ velocity } {}
	Particle(Vector2 position, Vector2 velocity, float lifespan) : position{ position }, velocity{ velocity }, lifespan{ lifespan } {}
	Particle(Vector2 position, Vector2 velocity, float lifespan, uint8_t r, uint8_t g, uint8_t b, uint8_t a) : position{ position }, velocity{ velocity }, lifespan{ lifespan }, r { r }, g{ g }, b{ b }, a{ a } {}

	void Update(float dt);
	void Draw(Renderer& renderer);
};