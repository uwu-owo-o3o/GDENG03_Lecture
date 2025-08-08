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
	//Test case 1 & 2
	//Cube* cube1 = new Cube("Cube 1");
	//cube1->setPosition(0.0, 0.9, 0.0);
	//this->gameObjects.push_back(cube1);

	//Cube* cube2 = new Cube("Cube 2");
	//cube2->setPosition(-1.5, 2.0, 0.0);
	//this->gameObjects.push_back(cube2);

	//Cube* cube3 = new Cube("Cube 3");
	//cube3->setPosition(-1.5, 3.0, 2.0);
	//this->gameObjects.push_back(cube3);

	//Plane* plane = new Plane("Plane 1");
	//plane->setPosition(-1.0, 0, 0);
	//plane->setScale(2, 1, 2);
	//this->gameObjects.push_back(plane);

	//Test case 3 & 4
	/*Cube* wall1 = new Cube("Wall 1");
	wall1->setPosition(-4.73, 2.43, -0.01);
	wall1->setScale(0.5, 5, 10);
	this->gameObjects.push_back(wall1);

	Cube* wall2 = new Cube("Wall 2");
	wall2->setPosition(-0.04, 2.43, 4.74);
	wall2->setScale(10, 5, 0.5);
	this->gameObjects.push_back(wall2);

	Cube* wall3 = new Cube("Wall 3");
	wall3->setPosition(-0.04, 0.98, -4.75);
	wall3->setScale(10, 2, 0.5);
	this->gameObjects.push_back(wall3);

	Cube* wall4 = new Cube("Wall 4");
	wall4->setPosition(4.77, 0.98, -0.01);
	wall4->setScale(0.5, 2, 10);
	this->gameObjects.push_back(wall4);

	Capsule* capsule = new Capsule("Capsule");
	capsule->setPosition(0.23, 1.46, -0.25);
	capsule->setScale(1, 1, 1);
	this->gameObjects.push_back(capsule);

	Plane* plane = new Plane("Plane 1");
	plane->setPosition(0.0, 0, 0);
	plane->setScale(4, 1, 4);
	this->gameObjects.push_back(plane);*/

	//Test case 5
	//Cube* wall1 = new Cube("Wall 1");
	//wall1->setPosition(-4.73, 2.43, -0.01);
	//wall1->setScale(0.5, 5, 10);
	//this->gameObjects.push_back(wall1);

	//Cube* wall2 = new Cube("Wall 2");
	//wall2->setPosition(-0.04, 2.43, 4.74);
	//wall2->setScale(10, 5, 0.5);
	//this->gameObjects.push_back(wall2);

	//Cube* wall3 = new Cube("Wall 3");
	//wall3->setPosition(-0.04, 0.98, -4.75);
	//wall3->setScale(10, 2, 0.5);
	//this->gameObjects.push_back(wall3);

	//Cube* wall4 = new Cube("Wall 4");
	//wall4->setPosition(4.77, 0.98, -0.01);
	//wall4->setScale(0.5, 2, 10);
	//this->gameObjects.push_back(wall4);

	Plane* plane = new Plane("Plane 1");
	plane->setPosition(0, -5, 0);
	plane->setScale(4, 1, 4);
	PhysicsComponent* component = new PhysicsComponent("Plane Physics Component", plane);
	component->getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
	plane->attachComponent(component);
	this->gameObjects.push_back(plane);
	
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
	int spawnNum = 50;
	for (int i = 0; i < spawnNum; i++) {
		std::string cube_name = "Cube " + std::to_string(i);
		std::string component_name = "Cube Physics Component " + std::to_string(i);
		Cube* cube = new Cube(cube_name);
		cube->hasPhysics = true;
		PhysicsComponent* component = new PhysicsComponent(component_name, cube);
		cube->attachComponent(component);

		this->gameObjects.push_back(cube);
	}
}
