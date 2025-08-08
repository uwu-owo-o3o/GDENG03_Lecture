#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"
#include "Prerequisites.h"

class Sphere : public AGameObject
{
	private:
		std::vector<vertex> cube_list;
		std::vector<unsigned int> index_list;
	public:
		bool isTextured = false;

	public:
		Sphere(std::string name);
		~Sphere();
	public:
		virtual void create() override;
		virtual void update(float deltaTime, int width, int height) override;
		virtual void draw() override;

	private:
		void MakeSphere(vertex* list, unsigned int* index_list);

};

