#include "AGameObject.h"

AGameObject::AGameObject(std::string name)
{
	this->name = name;
	this->pos = Vector3D(0, 0, 0);
	this->rot = Vector3D(0, 0, 0);	
	this->scale = Vector3D(1, 1, 1);
}

AGameObject::~AGameObject()
{

}

void AGameObject::setPosition(float x, float y, float z)
{
	
}

void AGameObject::setPosition(Vector3D pos)
{
}

Vector3D AGameObject::getLocalPos()
{
	return Vector3D();
}

void AGameObject::setScale(float x, float y, float z)
{
	
}

void AGameObject::setScale(Vector3D scale)
{
}

Vector3D AGameObject::getLocalScale()
{
	return Vector3D();
}

void AGameObject::setRot(float x, float y, float z)
{
}

void AGameObject::setRot(Vector3D scale)
{
}

Vector3D AGameObject::getLocalRot()
{
	return Vector3D();
}
