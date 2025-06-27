#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"
#include "Prerequisites.h"

class Cube : public AGameObject
	{
	public:
		Cube(std::string name);
		~Cube();

	public:
		virtual void create() override;
		virtual void update(float deltaTime, int width, int height) override;
		virtual void draw() override;
};

