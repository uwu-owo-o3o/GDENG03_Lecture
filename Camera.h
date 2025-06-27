#pragma once
#include "AGameObject.h"

class Camera : public AGameObject
{
	public:
		Camera(std::string name);
		~Camera();

	public:
		virtual void create() override;
		virtual void update(float deltaTime, int width, int height) override;
		virtual void draw() override;

		void moveOnKey(int key);
		void OnKeyRelease();
		 
		void setWindowReference(RECT window);
		
	public:
		RECT windowRef;

	public:
		constant cc;

	private:
		Matrix4x4 m_world_cam;

	private:
		float m_old_time = 0;
		float m_new_time = 0;
		float m_delta_time = 0;

		float m_forward = 0;
		float m_rightward = 0;
		float m_upward = 0;
};

