#pragma once
#include "fstream"
#include "vector"
#include "GameObjectManager.h"

class SceneSave
{
	public:
		SceneSave();
		~SceneSave();
	public:
		void saveScene();
		int checkObjectType(AGameObject* gameObject);
};

