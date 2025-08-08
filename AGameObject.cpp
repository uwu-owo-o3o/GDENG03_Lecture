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

float* AGameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 scale_m;
	scale_m.setIdentity();
	scale_m.setScale(Vector3D(1, 1, 1));

	Matrix4x4 rot_mx;
	rot_mx.setIdentity();
	rot_mx.setRotationX(this->rot.m_x);

	Matrix4x4 rot_my;
	rot_my.setIdentity();
	rot_my.setRotationY(this->rot.m_y);

	Matrix4x4 rot_mz;
	rot_mz.setIdentity();
	rot_mz.setRotationZ(this->rot.m_z);

	Matrix4x4 rotation_m;
	rotation_m = rot_mx * rot_my * rot_mz;

	Matrix4x4 translation_m;
	translation_m.setIdentity();
	translation_m.setTranslation(this->pos);

	Matrix4x4 transform_m = scale_m * rotation_m * translation_m;

	return transform_m.getMatrix();
}

void AGameObject::setPhysicsMatrix(float matrix[16])
{    
	
	float tempMatrix[4][4];
	for (int row = 0; row < 4; ++row)
		for (int col = 0; col < 4; ++col)
			tempMatrix[row][col] = matrix[row * 4 + col];

	Matrix4x4 physicsTransform;
	physicsTransform.setMatrix(tempMatrix);

	Matrix4x4 scale_m;
	scale_m.setScale(this->scale);

	this->physicsMatrix = physicsTransform;

	this->hasPhysics = true;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	std::cout << "componentList size: " << componentList.size() << std::endl;
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (component == this->componentList[i]) {
			index = i;
		}
	}

	if (index > -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentByName(std::string name)
{
	AComponent* target = nullptr;
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (name == this->componentList[i]->getName()) {
			index = i;
		}
	}

	if (index > -1) {
		target = this->componentList[index];
	}

	return target;
}

AComponent* AGameObject::findComponentOfType(ComponentType type, std::string name)
{
	AComponent* target = nullptr;
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (name == this->componentList[i]->getName() && type == this->componentList[i]->getType()) {
			index = i;
		}
	}

	if (index > -1) {
		target = this->componentList[index];
	}

	return target;
}

std::vector<AComponent*> AGameObject::getComponentsOfType(ComponentType type)
{
	std::vector<AComponent*> holder = std::vector<AComponent*>();
	std::cout << "componentList size: " << componentList.size() << std::endl;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (type == this->componentList[i]->getType()) {
			holder.push_back(this->componentList[i]);
		}
	}
	std::cout << "holder size: " << holder.size() << std::endl;
	return holder;
}
