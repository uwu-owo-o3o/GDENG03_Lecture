#pragma once
#include "SceneSave.h"
#include "LoadScene.h"

class SceneHandler
{
	public:
		SceneHandler();
		~SceneHandler();

	public:
		SceneSave* sceneSaver;
		LoadScene* sceneLoader;

	public:
		static SceneHandler* Instance;
		static void initialize();
};

