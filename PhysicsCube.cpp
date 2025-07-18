#include "PhysicsCube.h"

PhysicsCube::PhysicsCube(std::string name) : Cube(name)
{
	this->create();
}

PhysicsCube::~PhysicsCube()
{
}

void PhysicsCube::create()
{
	Cube::create();
}

void PhysicsCube::update(float deltaTime, int width, int height)
{
	Cube::update(deltaTime, width, height);
}

void PhysicsCube::draw()
{
	Cube::draw();
}
