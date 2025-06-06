#pragma once
#include "Vertex.h"
#include "Particle.h"
#include "vector"
#include "Prerequisites.h"
#include "iostream"
class ParticleSystem
{
	public:
		ParticleSystem();
		~ParticleSystem();

	public:
		void SpawnParticles();
		void setConstantRef(constant* ccRef);
		void setConstantBufferPtr(ConstantBufferPtr cb_reference);

		void updateParticles();
		void drawParticles();

	public:
		std::vector<Particle*> spawnedParticles;

	private:
		constant* ccRef;
		ConstantBufferPtr cb_reference;

		int maxSpawned = 1;


};

