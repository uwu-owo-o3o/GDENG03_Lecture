#pragma once
#include "Camera.h"
#include "Prerequisites.h"

class SceneCameraHandler
{
	public:
		SceneCameraHandler();
		~SceneCameraHandler();

	public:
		void initialize();
		void destroy();

	public:
		void update(float deltaTime, int width, int height);

	public:
		static SceneCameraHandler* getInstance();
		Camera* getSceneCamera();
	private:
		static SceneCameraHandler* shared_instance;
		Camera* sceneCamera;
};

