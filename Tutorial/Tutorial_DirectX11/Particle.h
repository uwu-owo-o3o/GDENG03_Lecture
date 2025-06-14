#pragma once
#include "Prerequisites.h"
#include "RenderObject.h"
#include "iostream"
#include "algorithm"

class Particle : public RenderObject
{
	public:
		Particle(constant* ref);
		~Particle();

	public:
		void onUpdate() override;
		void updatePosition();
		void updateVelocity();
		void resetForce();

		void addGravity();

	public:
		Vector3D velocity;
		Vector3D acceleration;
		
		Vector3D accumulatedForce;

		Vector3D startColor;
		Vector3D endColor;

		float mass = 5.0f;
		float damping = 0.9f;
		float speed = 5.0f;

	public:
		float lifeSpan;
		float lifeTicks;

		bool toBeDestroyed;
		

};

