#pragma once
#include "string"
#include "vector"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vertex.h"
#include "Point.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"
#include "AComponent.h"

class AGameObject
{
	public:
		AGameObject(std::string name);
		~AGameObject();

	public:
		virtual void create() = 0;
		virtual void update(float deltaTime, int width, int height) = 0;
		virtual void draw() = 0;

		void setPosition(float x, float y, float z);
		void setPosition(Vector3D pos);
		Vector3D getLocalPos();

		void setScale(float x, float y, float z);
		void setScale(Vector3D scale);
		Vector3D getLocalScale();

		void setRot(float x, float y, float z);
		void setRot(Vector3D scale);
		Vector3D getLocalRot();
		
		float* getPhysicsLocalMatrix();
		void setPhysicsMatrix(float matrix[16]);

	public:
		void attachComponent(AComponent* component);
		void detachComponent(AComponent* component);

		AComponent* findComponentByName(std::string name);
		AComponent* findComponentOfType(ComponentType type, std::string name);
		std::vector<AComponent*> getComponentsOfType(ComponentType type);

	protected:
		VertexBufferPtr m_vb;
		ConstantBufferPtr m_cb;
		IndexBufferPtr m_ib;

		VertexShaderPtr m_vs;
		PixelShaderPtr m_ps;
	
	protected:
		constant cc;

	protected:
		Vector3D pos;
		Vector3D scale;
		Vector3D rot;

		std::string name;

	public:
		std::vector<AComponent*> componentList;

		Matrix4x4 physicsMatrix;
		bool hasPhysics = false;


};

