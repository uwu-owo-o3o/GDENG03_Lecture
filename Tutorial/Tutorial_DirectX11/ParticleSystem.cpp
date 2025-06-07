#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	srand(time(0));
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::spawnParticles()
{
	//for (int i = 0; i < this->maxSpawned; i++) {
		Particle* newParticle = new Particle(ccRef, this->cb_reference);
		//std::cout << "Particle # " << i << std::endl;
		
		float spawn_angle = this->getRandNum(0.0f, 2.0f * 3.14f);
		float target_angle = this->getRandNum(0.0f, 2.0f * 3.14f);

		Vector3D spawnPos = Vector3D(0, 0, 0);
		Vector3D dir = spawnPos.Normalize(this->getTargetPos(target_angle) - spawnPos);

		newParticle->obj_pos = spawnPos;
		newParticle->velocity = dir * newParticle->speed;
		this->spawnedParticles.push_back(newParticle);
	//}

		Particle* newParticle1 = new Particle(ccRef, this->cb_reference);
		//std::cout << "Particle # " << i << std::endl;
		newParticle1->startColor = Vector3D(1.0f, 0.0f, 0.0f);

		float spawn_angle1 = this->getRandNum(0.0f, 2.0f * 3.14f);
		float target_angle1 = this->getRandNum(0.0f, 2.0f * 3.14f);

		Vector3D spawnPos1 = Vector3D(5, 5, 0);
		Vector3D dir1 = spawnPos1.Normalize(this->getTargetPos(target_angle) - spawnPos);

		newParticle1->obj_pos = spawnPos1;
		newParticle1->velocity = dir1 * newParticle1->speed;
		this->spawnedParticles.push_back(newParticle1);
}

Vector3D ParticleSystem::getSpawnPos(float angle)
{
	float dist = this->getRandNum(0.0f, 1.0f) * spawnRadius;

	float x = dist * cos(angle);
	float y = 0.0f;
	float z = dist * sin(angle);

	Vector3D startPos = Vector3D(x, y, z);
	std::cout << "startPos: " << x << " " << y << " " << z << std::endl;
	return startPos;
}

Vector3D ParticleSystem::getTargetPos(float angle)
{
	float dist = this->getRandNum(0.0f, 1.0f) * targetRadius;

	float x = dist * cos(angle);
	float y = this->coneHeight;
	float z = dist * sin(angle);

	Vector3D targetPos = Vector3D(x, y, z);
	std::cout << "targetPos: " << x << " " << y << " " << z << std::endl;
	return targetPos;
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
		this->spawnedParticles[0]->draw();
	}
}

float ParticleSystem::getRandNum(float lb, float ub)
{
	float num = lb + (ub - lb) * ((float)rand() / (float)RAND_MAX);
	return num;
}
