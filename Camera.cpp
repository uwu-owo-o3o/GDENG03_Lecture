#include "Camera.h"

Camera::Camera(std::string name) : AGameObject(name)
{
	this->create();
}

Camera::~Camera()
{
}

void Camera::create()
{
	std::cout << "called camera create" << std::endl;
	m_world_cam.setTranslation(Vector3D(0, 1, -5));
}

void Camera::update(float deltaTime, int width, int height)
{
	Matrix4x4 temp;
	cc.m_world.setScale(Vector3D(1, 1, 1));

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(this->rot.m_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->rot.m_y);
	world_cam *= temp;

	Vector3D new_pos =  m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.05f);
	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.05f);
	new_pos = new_pos + world_cam.getYDirection() * (m_upward * 0.05f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();

	cc.m_view = world_cam;

}

void Camera::draw()
{
	std::cout << "Draw Function is called." << std::endl;

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
	else if (key == 'Z')
	{
		m_upward = -1.0f;
	}
	else if (key == 'X')
	{
		m_upward = 1.0f;
	}
	else if (key == 'R')
	{
		this->rot.m_y += 0.707 * m_delta_time;
	}

}

void Camera::OnKeyRelease()
{
	this->m_forward = 0.0f;
	this->m_rightward = 0.0f;
	this->m_upward = 0.0f;
}

void Camera::setWindowReference(RECT og_window) {
	this->windowRef = og_window;
}


