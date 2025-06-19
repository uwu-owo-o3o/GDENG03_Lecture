#pragma once
#include "Prerequisites.h"
#include "ConstantBuffer.h"
#include "Vertex.h"
#include "Matrix4x4.h"

class PointLight
{

	public:
		PointLight();
		~PointLight();

	public:
		void initialize();
		void onUpdate();
		void onKeyMove(int key);

	public:
		constant constantRef;
		Vector4D lightPos;

	private:
		Matrix4x4 m_light_rot_matrix;
		ConstantBufferPtr cb_ref;

	public:
		void setConstantBufferRef(ConstantBufferPtr cb);

};

