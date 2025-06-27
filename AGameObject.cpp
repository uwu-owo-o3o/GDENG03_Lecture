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
	this->pos = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->pos = pos;
}

Vector3D AGameObject::getLocalPos()
{
	return this->pos;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->scale = Vector3D(x,y, z);
}

void AGameObject::setScale(Vector3D scale)
{
	this->scale = scale;
}

Vector3D AGameObject::getLocalScale()
{
	return this->scale;
}

void AGameObject::setRot(float x, float y, float z)
{
	this->rot = Vector3D(x, y, z);
}

void AGameObject::setRot(Vector3D scale)
{
	this->rot = rot;
}

Vector3D AGameObject::getLocalRot()
{
	return this->rot;
}
