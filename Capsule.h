#pragma once
#include "AGameObject.h"
#include "SceneCameraHandler.h"
#include "Prerequisites.h"

class Capsule : public AGameObject
{
	public:
		Capsule(std::string name);
		~Capsule();

	public:
		virtual void create() override;
		virtual void update(float deltaTime, int width, int height) override;
		virtual void draw() override;
		void MakeCapsule(vertex* list, unsigned int* index_list);

};

