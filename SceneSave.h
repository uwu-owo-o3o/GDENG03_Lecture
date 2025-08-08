#pragma once
#include "fstream"
#include "vector"
#include "PhysicsComponent.h"
#include "GameObjectManager.h"

class SceneSave
{
	public:
		SceneSave();
		~SceneSave();
	public:
		void saveScene();
		int checkObjectType(AGameObject* gameObject);
		int checkBodyType(reactphysics3d::BodyType type);
		PhysicsComponent* getPhysicsComponent(AGameObject* gameObject);
};

