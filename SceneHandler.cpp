#include "SceneHandler.h"

SceneHandler* SceneHandler::Instance = nullptr;

SceneHandler::SceneHandler()
{
	this->sceneSaver = new SceneSave();
	this->sceneSaver = new SceneSave();
}

SceneHandler::~SceneHandler()
{
}

void SceneHandler::initialize()
{
	if (Instance == nullptr) {
		Instance = new SceneHandler();
	}
}



