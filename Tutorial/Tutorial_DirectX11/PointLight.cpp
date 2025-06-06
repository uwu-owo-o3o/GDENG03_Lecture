#include "PointLight.h"
#include "GraphicsEngine.h"

PointLight::PointLight()
{
}

PointLight::~PointLight()
{

}

void PointLight::initialize()
{
	lightPos = Vector4D(0, 2, 0, 0);
	m_light_rot_matrix.setIdentity();
	m_light_rot_matrix.setRotationY(0.0f);
}

void PointLight::onUpdate()
{
	//constantRef.m_light_position = lightPos;
	//constantRef.m_light_direction = m_light_rot_matrix.getZDirection();
}

void PointLight::onKeyMove(int key)
{
	if (key == 'I') {
		lightPos.m_x += 30;
	}
	else if (key == 'K') {
		lightPos.m_x -= 30;
	}
}


void PointLight::setConstantBufferRef(ConstantBufferPtr cb) {
	this->cb_ref = cb;
}
