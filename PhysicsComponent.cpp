#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "AGameObject.h"

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner) : AComponent(name, ComponentType::Physics, owner)
{
    this->name = name;
    this->owner = owner;
	this->type = ComponentType::Physics;
	PhysicsSystem::Instance->registerComponent(this);
	PhysicsCommon* physicsCommon = PhysicsSystem::Instance->getPhysicsCommon();
	PhysicsWorld* physicsWorld = PhysicsSystem::Instance->getPhysicsWorld();

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	Transform transform; 
	transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());

	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x, scale.m_y, scale.m_z)); 
	
	if (physicsWorld != nullptr) {
		std::cout << "physicsworld is not null" << std::endl;
	}
	
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, Transform::identity());
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();

	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setPhysicsMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setPhysicsMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return this->rigidBody;
}

float PhysicsComponent::getMass()
{
	return this->mass;
}

