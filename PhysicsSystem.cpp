#include "PhysicsSystem.h"
#include "EngineTime.h"
#include "PhysicsComponent.h"

PhysicsSystem* PhysicsSystem::Instance = nullptr;

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 20;
	settings.isSleepingEnabled = false;
	settings.gravity = Vector3(0, -9.81, 0);

	this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

PhysicsSystem::~PhysicsSystem()
{
}

void PhysicsSystem::initialize()
{
	if (Instance == nullptr) {
		Instance = new PhysicsSystem();
	}
}

void PhysicsSystem::registerComponent(PhysicsComponent* component)
{
	this->componentList.push_back(component);
	this->componentTable[component->getName()] = component;
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (component == this->componentList[i]) {
			index = i;
		}
	}

	if (index > -1) {
		this->componentList.erase(this->componentList.begin() + index);
		this->componentTable.erase(component->getName());
	}
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (name == this->componentList[i]->getName()) {
			index = i;
		}
	}

	if (index > -1) {
		this->componentList.erase(this->componentList.begin() + index);
		this->componentTable.erase(name);
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name)
{
	PhysicsComponent* target = nullptr;
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (name == this->componentList[i]->getName()) {
			index = i;
		}
	}

	if (index > -1) {
		target = this->componentList[index];
	}

	return target;
}

std::vector<PhysicsComponent*> PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
	if (EngineTime::getDeltaTime() <= 0.0f) return;
	this->physicsWorld->update(EngineTime::getDeltaTime());
	for (PhysicsComponent* component : this->componentList) {
		component->perform(EngineTime::getDeltaTime());
	}
	
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}

