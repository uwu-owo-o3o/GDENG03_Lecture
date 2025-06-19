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

		void updateParticles();
		void destroyParticles();
		void drawParticles();

		void continuousSpawn();

		float getRandNum(float lb, float u);

	public:
		std::vector<Particle*> spawnedParticles = std::vector<Particle*>();
		int maxSpawned = 5;

	public:
		float spawnRadius = 1.0f; 
		Vector3D coneCenter = Vector3D(0, 0, 0);
		float targetRadius = 3.0f;
		float coneHeight = 5.0f;

	public:
		float spawnThreshold;
		float spawnTicks;

		float m_old_time = 0;
		float m_new_time = 0;
		float m_delta_time = 0;

	protected:
		constant* camRef;

		




};

