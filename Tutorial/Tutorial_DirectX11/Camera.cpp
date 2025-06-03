#include "Camera.h"
#include "GraphicsEngine.h"
#include "ConstantBuffer.h"

Camera::Camera()
{

}

Camera::~Camera()
{
}

void Camera::initialize()
{
	m_world_cam.setTranslation(Vector3D(0, 1, -2));

	constant cc;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void Camera::onUpdate()
{
	constant cc;
	Matrix4x4 temp;
	Matrix4x4 m_light_rot_matrix;

	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(0.0f);

	cc.m_light_direction = m_light_rot_matrix.getZDirection();


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

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.0005f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.0005f);

	world_cam.setTranslation(new_pos);

	cc.m_cam_pos = new_pos;
	m_world_cam = world_cam;

	world_cam.inverse();

	cc.m_view = world_cam;

	cc.m_proj.setOrthoLH(
		(this->windowRef.right - this->windowRef.left) / 400.0f,
		(this->windowRef.bottom - this->windowRef.top) / 400.0f,
		-4.0f,
		4.0f
	);

	int width = (this->windowRef.right - this->windowRef.left);
	int height = (this->windowRef.bottom - this->windowRef.top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);


}

void Camera::moveOnKey(int key)
{
	if (key == 'W')
	{
		//m_rot_x += 0.707 * m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 0.707 * m_delta_time;
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 0.707 * m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 0.707 * m_delta_time;
		m_rightward = 1.0f;
	}
	else if (key == 'R')
	{
		m_rot_y += 0.707 * m_delta_time;

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
