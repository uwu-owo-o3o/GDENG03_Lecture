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
		void spawnParticles();
		Vector3D getSpawnPos(float angle);
		Vector3D getTargetPos(float angle);

		void setConstantRef(constant* ccRef);
		void setConstantBufferPtr(ConstantBufferPtr cb_reference);

		void updateParticles();
		void drawParticles();

		float getRandNum(float lb, float u);

	public:
		std::vector<Particle*> spawnedParticles = std::vector<Particle*>();
		int maxSpawned = 2;

	public:
		float spawnRadius = 1.0f; 
		Vector3D coneCenter = Vector3D(0, 0, 0);
		float targetRadius = 3.0f;
		float coneHeight = 5.0f;

	protected:
		constant* ccRef;
		ConstantBufferPtr cb_reference;

		




};

