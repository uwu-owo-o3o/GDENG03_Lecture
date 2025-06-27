#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"
#include "Prerequisites.h"

class Plane : public AGameObject
{
	public:
		Plane(std::string name);
		~Plane();

	public:
		virtual void create() override;
		virtual void update(float deltaTime, int width, int height) override;
		virtual void draw() override;
};

