#pragma once
#include "Cube.h"
class PhysicsCube : public Cube
{
	public:
		PhysicsCube(std::string name);
		~PhysicsCube();

	public:
		virtual void create() override;
		virtual void update(float deltaTime, int width, int height) override;
		virtual void draw() override;
};

