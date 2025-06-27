#pragma once
#include "string"
#include "Vector3D.h"
#include "Prerequisites.h"

class AGameObject
{
	public:
		AGameObject(std::string name);
		~AGameObject();

	public:
		virtual void update(float deltaTime) = 0;
		virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

		void setPosition(float x, float y, float z);
		void setPosition(Vector3D pos);
		Vector3D getLocalPos();

		void setScale(float x, float y, float z);
		void setScale(Vector3D scale);
		Vector3D getLocalScale();

		void setRot(float x, float y, float z);
		void setRot(Vector3D scale);
		Vector3D getLocalRot();

	private:
		Vector3D pos;
		Vector3D scale;
		Vector3D rot;
		std::string name;


};

