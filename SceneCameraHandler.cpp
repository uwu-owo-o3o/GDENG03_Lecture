#include "SceneCameraHandler.h"

SceneCameraHandler* SceneCameraHandler::shared_instance = nullptr;

SceneCameraHandler::SceneCameraHandler()
{
}

SceneCameraHandler::~SceneCameraHandler()
{
}

void SceneCameraHandler::initialize()
{
	if (shared_instance == nullptr) {
		shared_instance = new SceneCameraHandler();
		shared_instance->sceneCamera = new Camera("Scene Camera");
	}

}

void SceneCameraHandler::destroy()
{
}

void SceneCameraHandler::update(float deltaTime, int width, int height)
{
	this->sceneCamera->update(deltaTime, width, height);
}

SceneCameraHandler* SceneCameraHandler::getInstance()
{
	return shared_instance;
}

Camera* SceneCameraHandler::getSceneCamera()
{
	return this->sceneCamera;
}
