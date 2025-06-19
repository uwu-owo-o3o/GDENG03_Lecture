#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
{
	srand(time(0));
	this->spawnTicks = 1.0f;
	this->spawnThreshold = 1.0f;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::spawnParticles()
{
	for (int i = 0; i < this->maxSpawned; i++) {
		Particle* newParticle = new Particle(camRef);
		//std::cout << "Particle # " << i << std::endl;
		
		float spawn_angle = this->getRandNum(0.0f, 2.0f * 3.14f);
		float target_angle = this->getRandNum(0.0f, 2.0f * 3.14f);

		Vector3D spawnPos = this->getSpawnPos(spawn_angle);
		Vector3D dir = spawnPos.Normalize(this->getTargetPos(target_angle) - spawnPos);

		newParticle->obj_pos = spawnPos;
		newParticle->velocity = dir * newParticle->speed;
		this->spawnedParticles.push_back(newParticle);
	}
}

Vector3D ParticleSystem::getSpawnPos(float angle)
{
	float dist = sqrt(this->getRandNum(0.0f, 1.0f)) * spawnRadius;

	float x = dist * cos(angle);
	float y = 0.0f;
	float z = dist * sin(angle);

	Vector3D startPos = Vector3D(x, y, z);
	//std::cout << "startPos: " << x << " " << y << " " << z << std::endl;
	return startPos;
}

Vector3D ParticleSystem::getTargetPos(float angle)
{
	float dist = sqrt(this->getRandNum(0.0f, 1.0f)) * targetRadius;

	float x = dist * cos(angle);
	float y = this->coneHeight;
	float z = dist * sin(angle);

	Vector3D targetPos = Vector3D(x, y, z);
	//std::cout << "targetPos: " << x << " " << y << " " << z << std::endl;
	return targetPos;
}

void ParticleSystem::setConstantRef(constant* ccRef)
{
	this->camRef = ccRef;
}

void ParticleSystem::updateParticles()
{
	int curr_size = this->spawnedParticles.size();
	for (int i = 0; i < curr_size; i++) {
		this->spawnedParticles[i]->onUpdate();
	}

	this->destroyParticles();
}

void ParticleSystem::destroyParticles()
{
	int curr_size = this->spawnedParticles.size();
	std::vector<int> destroyIndices;

	for (int i = 0; i < curr_size; i++) {
		if (this->spawnedParticles[i]->toBeDestroyed) {
			destroyIndices.push_back(i);
		}
	}

	for (int i = destroyIndices.size() - 1; i >= 0; i--) {
		int index = destroyIndices[i];
		Particle* targetParticle = this->spawnedParticles[index];
		delete targetParticle;
		this->spawnedParticles.erase(this->spawnedParticles.begin() + index);
	}
}

void ParticleSystem::drawParticles()
{
	int curr_size = this->spawnedParticles.size();
	for (int i = 0; i < curr_size; i++) {
		this->spawnedParticles[i]->draw();
	}
}

void ParticleSystem::continuousSpawn() {
	
	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time) ? (this->m_new_time - this->m_old_time) / 1000.0f : 0;

	if (this->spawnTicks >= this->spawnThreshold) {
		this->spawnParticles();
		this->spawnTicks = 0.0f;
	}

	this->spawnTicks += this->m_delta_time;

}


float ParticleSystem::getRandNum(float lb, float ub)
{
	float num = lb + (ub - lb) * ((float)rand() / (float)RAND_MAX);
	return num;
}
