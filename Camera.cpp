#include "Camera.h"
#include "GraphicsEngine.h"
#include "ConstantBuffer.h"
#include <iostream>

Camera::Camera()
{

}

Camera::~Camera()
{
}

void Camera::initialize()
{
	m_world_cam.setTranslation(Vector3D(0, 1, -5));
}

void Camera::onUpdate()
{
	Matrix4x4 temp;
	cc.m_world.setScale(Vector3D(1, 1, 1));

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.05f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.05f);

	world_cam.setTranslation(new_pos);

	//cc.m_cam_pos = new_pos;
	m_world_cam = world_cam;

	world_cam.inverse();

	cc.m_view = world_cam;

	//cc.m_proj.setOrthoLH(
	//	(this->windowRef.right - this->windowRef.left) / 400.0f,
	//	(this->windowRef.bottom - this->windowRef.top) / 400.0f,
	//	-4.0f,
	//	4.0f
	//);

	int width = (this->windowRef.right - this->windowRef.left);
	int height = (this->windowRef.bottom - this->windowRef.top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time) ? (this->m_new_time - this->m_old_time) / 1000.0f : 0;

}

void Camera::moveOnKey(int key)
{
	if (key == 'W')
	{
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		m_rightward = 1.0f;
	}
	else if (key == 'R')
	{
		m_rot_y += 0.5f * m_delta_time;

	}
	else if (key == 'T')
	{
		m_rot_y -= 0.5f * m_delta_time;

	}
	else if (key == 'G')
	{
		m_rot_x += 0.5f * m_delta_time;

	}
	else if (key == 'H')
	{
		m_rot_x -= 0.5f * m_delta_time;

	}


}

void Camera::OnKeyRelease()
{
	this->m_forward = 0.0f;
	this->m_rightward = 0.0f;
}

void Camera::setWindowReference(RECT og_window) {
	this->windowRef = og_window;
}

Matrix4x4 Camera::getViewMatrix()
{
	return Matrix4x4();
}

