#include "GameObjectManager.h"
#include "PhysicsComponent.h"

GameObjectManager* GameObjectManager::Instance = nullptr;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::initialize()
{
	if (Instance == nullptr) {
		Instance = new GameObjectManager();
	}
}

void GameObjectManager::create()
{
	//Cube* cube = new Cube("Cube 1");
	//Cube* cube2 = new Cube("Cube 2");
	Plane* plane = new Plane("Plane 1");

	//PhysicsComponent* component = new PhysicsComponent("Physics Cube 1", cube);
	//cube->attachComponent(component);

	//PhysicsComponent* component2 = new PhysicsComponent("Physics Cube 2", cube2);
	//cube2->attachComponent(component2);

	PhysicsComponent* component1 = new PhysicsComponent("Physics Plane 1", plane);
	component1->getRigidBody()->setType(BodyType::KINEMATIC);
	plane->attachComponent(component1);
	//this->gameObjects.push_back(cube);
	//this->gameObjects.push_back(cube2);
	this->gameObjects.push_back(plane);

	//Sphere* sphere = new Sphere("Sphere 1");
	//this->gameObjects.push_back(sphere);
	Capsule* capsule = new Capsule("Sphere 1");
	this->gameObjects.push_back(capsule);
}

void GameObjectManager::update(float deltaTime, int width, int height)
{
	for (int i = 0; i < this->gameObjects.size(); i++) {
		this->gameObjects[i]->update(deltaTime, width, height);
	}
}

void GameObjectManager::draw()
{
	for (int i = 0; i < this->gameObjects.size(); i++) {
		this->gameObjects[i]->draw();
	}
}

void GameObjectManager::spawnCubes()
{
	int spawnNum = 5;
	for (int i = 0; i < spawnNum; i++) {
		std::string cube_name = "Cube " + std::to_string(i);
		std::string component_name = "Cube Physics Component " + std::to_string(i);
		Cube* cube = new Cube(cube_name);
		
		PhysicsComponent* component = new PhysicsComponent(component_name, cube);
		cube->attachComponent(component);

		this->gameObjects.push_back(cube);
	}
}
