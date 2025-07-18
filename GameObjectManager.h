#pragma once
#include "Cube.h"
#include "Plane.h"
#include "vector"

class GameObjectManager
{
	public:
		static GameObjectManager* Instance;

	public:
		GameObjectManager();
		~GameObjectManager();

	public:
		std::vector<AGameObject*> gameObjects;
		static void initialize();
		void create();
		void update(float deltaTime, int width, int height);
		void draw();
};

