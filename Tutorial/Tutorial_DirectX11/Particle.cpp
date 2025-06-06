#include "Particle.h"

Particle::Particle(constant* ref, ConstantBufferPtr cb_reference) : RenderObject()
{
	ccRef = ref;
	ccRef->startColor = Vector3D(0.5, 1, 1);
	ccRef->m_obj_scale = Vector4D(0.2, 0.2, 0.2, 1);
	
	obj_pos = Vector4D(3, 0, 1, 1);

	ccRef->m_obj_pos = obj_pos;

	this->velocity = Vector3D(0, 5,0);
	this->accumulatedForce = Vector3D(0, 10, 0);
	this->setConstantBufferRef(cb_reference);
	this->createMesh(L"Assets\\Meshes\\sphere.obj");
	this->initialize();		 
}

Particle::~Particle()
{

}

void Particle::onUpdate()
{
	this->acceleration = Vector3D(0, 0, 0);

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time) ? (this->m_new_time - this->m_old_time) / 1000.0f : 0;

	this->addGravity();

	this->updateVelocity();
	this->updatePosition();
	this->resetForce();
}

void Particle::updatePosition() {
	/*
	std::cout << "Velocity: " << velocity.m_x << " " << velocity.m_y << " " << velocity.m_z << std::endl;
	std::cout << "Acceleration: " << acceleration.m_x << " " << " " << acceleration.m_y << " " << acceleration.m_z << std::endl;*/

	Vector3D newPos = (velocity * m_delta_time) + (this->acceleration * m_delta_time * m_delta_time) / 2.0f;

	//std::cout << "New Pos: " << newPos.m_x << " " << newPos.m_y << " " << newPos.m_z << std::endl;
	this->obj_pos = this->obj_pos + Vector4D(newPos);


	//std::cout << "Obj Pos: " << obj_pos.m_x << " " << obj_pos.m_y << " " << obj_pos.m_z << std::endl;
	ccRef->m_obj_pos = this->obj_pos;
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

