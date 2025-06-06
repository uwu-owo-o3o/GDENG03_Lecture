#pragma once
#include "Prerequisites.h"
#include "RenderObject.h"

class Particle : public RenderObject
{
	public:
		Particle(constant* ref, ConstantBufferPtr cb_reference);
		~Particle();

	public:
		void onUpdate() override;

	public:
		constant* ccRef;
		Vector4D obj_scale;
		Vector4D obj_pos;
};

