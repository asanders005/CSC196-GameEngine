#include "Particle.h"

void Particle::Update(float dt)
{
	position = position + (velocity * dt);
	if (lifespan != 0) 
	{
		lifespan -= dt;
	}
}

void Particle::Draw(Renderer& renderer)
{
	if (lifespan >= 0)
	{
		renderer.SetColor(r, g, b, a);
		renderer.DrawRect(position, 3.0f, 3.0f);
	}
}
