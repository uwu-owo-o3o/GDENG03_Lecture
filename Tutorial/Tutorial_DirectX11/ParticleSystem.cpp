#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::SpawnParticles()
{
	if (ccRef != nullptr) {
		std::cout << "ccRef is null" << std::endl;
	}

	for (int i = 0; i < this->maxSpawned; i++) {
		Particle* newParticle = new Particle(ccRef, this->cb_reference);
		this->spawnedParticles.push_back(newParticle);
	}
}

void ParticleSystem::setConstantRef(constant* ccRef)
{
	this->ccRef = ccRef;
}

void ParticleSystem::setConstantBufferPtr(ConstantBufferPtr cb_reference)
{
	this->cb_reference = cb_reference;
}

void ParticleSystem::updateParticles()
{
	for (int i = 0; i < this->maxSpawned; i++) {
		this->spawnedParticles[i]->onUpdate();
	}
}

void ParticleSystem::drawParticles()
{
	for (int i = 0; i < this->maxSpawned; i++) {
		this->spawnedParticles[i]->draw();
	}
}
