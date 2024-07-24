#include "ParticleSystem.h"

void ParticleSystem::Update(float dt)
{
	for (auto& p : m_particles)
	{
		if (p.isActive) p.Update(dt);
	}
}

void ParticleSystem::Draw(Renderer& renderer)
{
	for (auto& p : m_particles)
	{
		if (p.isActive) p.Draw(renderer);
	}
}

void ParticleSystem::AddParticle(const Particle::Data& data)
{
	Particle* p = GetFreeParticle();
	if (p)
	{
		p->Initialize(data);
	}
}

void ParticleSystem::ClearParticles()
{
	for (auto& p : m_particles)
	{
		p.isActive = false;
	}
}

Particle* ParticleSystem::GetFreeParticle()
{
	for (auto& p : m_particles)
	{
		if (!p.isActive) return &p;
	}

	return nullptr;
}
