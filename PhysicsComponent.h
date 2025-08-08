#pragma once
#include "AComponent.h"
#include "iostream"
#include <reactphysics3d.h>
#include "Vector3D.h"

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
	public:
		PhysicsComponent(std::string name, AGameObject* owner);
		~PhysicsComponent();
		void perform(float deltaTime) override;

		RigidBody* getRigidBody();
		float getMass();
	private:
		float mass = 100.0f; //in kilograms
		RigidBody* rigidBody;
};