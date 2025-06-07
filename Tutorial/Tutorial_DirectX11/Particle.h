#pragma once
#include "Prerequisites.h"
#include "RenderObject.h"
#include "iostream"

class Particle : public RenderObject
{
	public:
		Particle(constant* ref, ConstantBufferPtr cb_reference);
		~Particle();

	public:
		void onUpdate() override;
		void updatePosition();
		void updateVelocity();
		void resetForce();

		void addGravity();

	public:
		constant* ccRef;
		Vector4D obj_scale;
		Vector4D obj_pos;

	public:
		Vector3D velocity;
		Vector3D acceleration;
		
		Vector3D accumulatedForce;

		Vector3D startColor;

		float mass = 5.0f;
		float damping = 0.9f;
		float speed = 5.0f;
		

};

