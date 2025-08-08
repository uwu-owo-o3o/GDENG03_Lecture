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
	//Test case 1
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
