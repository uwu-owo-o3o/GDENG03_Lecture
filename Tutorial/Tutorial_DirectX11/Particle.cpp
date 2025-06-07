#include "Particle.h"

Particle::Particle(constant* ref) : RenderObject()
{
	this->toBeDestroyed = false;

	this->lifeSpan = 5.0f;
	this->lifeTicks = 0.0f;

	camCC = ref;
	startColor = Vector3D(0.5, 0, 1.0);
	endColor = Vector3D(0.5, 0, 0.0);

	cc.m_obj_scale = Vector4D(0.5, 0.5, 0.5, 1);
	
	obj_pos = Vector4D(0, 0, 0, 1);


	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));

	this->accumulatedForce = Vector3D(0, 0, 0);	
	this->createMesh(L"Assets\\Meshes\\sphere.obj");
	this->initialize();		 

	if (this->m_mesh == nullptr) {
		std::cout << "mesh of particle is null" << std::endl;
	}
}

Particle::~Particle()
{
}

void Particle::onUpdate()
{
	if (this->lifeTicks >= this->lifeSpan) {
		this->toBeDestroyed = true;
	}

	lifeTicks += m_delta_time;

	if (toBeDestroyed) {
		return;
	}
	float timeLived = this->lifeTicks / this->lifeSpan;
	timeLived = std::clamp(timeLived, 0.0f, 1.0f);
	cc.currentColor = startColor.lerp(startColor, endColor, timeLived);
	
	cc.m_obj_pos = obj_pos;

	cc.m_cam_pos = camCC->m_cam_pos;
	cc.m_view = camCC->m_view;
	cc.m_proj = camCC->m_proj;
	cc.m_world = camCC->m_world;

	this->acceleration = Vector3D(0, 0, 0);

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time) ? (this->m_new_time - this->m_old_time) / 1000.0f : 0;

	this->addGravity();

	this->updateVelocity();
	this->updatePosition();
	this->resetForce();

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void Particle::updatePosition() {
	/*
	std::cout << "Velocity: " << velocity.m_x << " " << velocity.m_y << " " << velocity.m_z << std::endl;
	std::cout << "Acceleration: " << acceleration.m_x << " " << " " << acceleration.m_y << " " << acceleration.m_z << std::endl;*/

	Vector3D newPos = (velocity * m_delta_time) + (this->acceleration * m_delta_time * m_delta_time) / 2.0f;

	//std::cout << "New Pos: " << newPos.m_x << " " << newPos.m_y << " " << newPos.m_z << std::endl;
	this->obj_pos = this->obj_pos + Vector4D(newPos);


	//std::cout << "Obj Pos: " << obj_pos.m_x << " " << obj_pos.m_y << " " << obj_pos.m_z << std::endl;
	cc.m_obj_pos = this->obj_pos;
}

void Particle::updateVelocity() {
	this->acceleration = this->acceleration + (accumulatedForce / mass);
	this->velocity = this->velocity + (this->acceleration * m_delta_time);
	this->velocity = this->velocity * powf(damping, m_delta_time);
}

void Particle::resetForce() {
	this->accumulatedForce = Vector3D(0, 0, 0);
	this->acceleration = Vector3D(0, 0, 0);
}

void Particle::addGravity()
{
	this->accumulatedForce = this->accumulatedForce + Vector3D(0, -9.8, 0);
}

