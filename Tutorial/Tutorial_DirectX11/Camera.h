#pragma once
#include "Prerequisites.h"
#include "Vertex.h"
#include <Windows.h>

class Camera
{
	public:
		Camera();
		~Camera();

	public:
		void initialize();
		void onUpdate();

		void moveOnKey(int key);
		void OnKeyRelease();

		void setWindowReference(RECT window);

	public:
		RECT windowRef;

	public:
		constant cc;

	private:
		Matrix4x4 m_world_cam;

		float m_rot_x = 0.0f;
		float m_rot_y = 0.0f;
		float m_rot_z = 0.0f;

		float m_forward = 0.0f;
		float m_rightward = 0.0f;

	private:
		float m_old_time = 0;
		float m_new_time = 0;
		float m_delta_time = 0;
};

