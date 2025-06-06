#include "Particle.h"

Particle::Particle(constant* ref, ConstantBufferPtr cb_reference) : RenderObject()
{
	ccRef = ref;
	ccRef->startColor = Vector3D(0.5, 1, 1);

	this->setConstantBufferRef(cb_reference);
	this->createMesh(L"Assets\\Meshes\\sphere.obj");
	this->initialize();
		 
}

Particle::~Particle()
{
}

void Particle::onUpdate()
{

}




