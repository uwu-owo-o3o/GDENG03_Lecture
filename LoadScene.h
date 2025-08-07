#pragma once
#include "fstream"
#include "sstream"
#include "vector"
#include "string"
#include "GameObjectManager.h"

class LoadScene
{
	public:
		LoadScene();
		~LoadScene();
	public:
		void loadScene();
		void createPrimitive(int type, std::string name, Vector3D position, Vector3D scale, Vector3D rotation);
};

