#include "SceneSave.h"
#include "Cube.h"
#include "Plane.h"

SceneSave::SceneSave()
{
}

SceneSave::~SceneSave()
{
}

void SceneSave::saveScene()
{
	std::ofstream MyFile("saved_scene.level");
		
	std::vector<AGameObject*> gameObjects = GameObjectManager::Instance->gameObjects;

	for (AGameObject* object : gameObjects) {
		MyFile << "Name: " << object->name << std::endl;
		MyFile << "Position: " << object->pos.m_x << " " << object->pos.m_y << " " << object->pos.m_z << std::endl;
		MyFile << "Scale: " << object->pos.m_x << " " << object->pos.m_y << " " << object->pos.m_z << std::endl;
		MyFile << "Rotation: " << object->rot.m_x << " " << object->rot.m_y << " " << object->rot.m_z << std::endl;
		MyFile << "Type: " << this->checkObjectType(object) << std::endl;
	}

	MyFile.close();
}

int SceneSave::checkObjectType(AGameObject* gameObject)
{
	int type = -1;
	if (Cube* cube = dynamic_cast<Cube*>(gameObject)) {
		type = 0;
	}
	else if (Plane* plane = dynamic_cast<Plane*>(gameObject)) {
		type = 1;
	}
	return type;
}

