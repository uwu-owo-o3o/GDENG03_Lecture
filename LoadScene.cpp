#include "LoadScene.h"

LoadScene::LoadScene()
{
}

LoadScene::~LoadScene()
{
}

void LoadScene::loadScene()
{
	std::ifstream MyFile("saved_scene.level");
    if (!MyFile.is_open()) {
        std::cerr << "Failed to open file." << std::endl;
    }

    Vector3D position = Vector3D();
    Vector3D scale = Vector3D();
    Vector3D rotation = Vector3D();
    std::string name = "";
    int type = -1;
    
    std::string line;
    while (std::getline(MyFile, line)) {
        if (line.empty()) continue;

        std::string name_line = line.substr(line.find(":") + 1);
        name = name_line;

        std::getline(MyFile, line); // Position
        std::istringstream pos_line(line.substr(line.find(":") + 1));
        pos_line >> position.m_x >> position.m_y >> position.m_z;

        std::getline(MyFile, line); // Scale
        std::istringstream scale_line(line.substr(line.find(":") + 1));
        scale_line >> scale.m_x >> scale.m_y >> scale.m_z;

        std::getline(MyFile, line); // Rotation
        std::istringstream rot_line(line.substr(line.find(":") + 1));
        rot_line >> rotation.m_x >> rotation.m_y >> rotation.m_z;

        std::getline(MyFile, line); // Type
        type = std::stoi(line);

        this->createPrimitive(type, name, position, scale, rotation);
    }

}

void LoadScene::createPrimitive(int type, std::string name, Vector3D position, Vector3D scale, Vector3D rotation)
{
    switch (type) {
        case 0: {
            Cube* cube = new Cube(name);
            cube->pos = position;
            cube->scale = scale;
            cube->rot = rotation;
            std::cout << "cube pos: " << cube->pos.m_x << " " << cube->pos.m_y << " " << cube->pos.m_z << std::endl;
            std::cout << "cube scale: " << cube->scale.m_x << " " << cube->scale.m_y << " " << cube->scale.m_z << std::endl;
            std::cout << "cube rot: " << cube->rot.m_x << " " << cube->rot.m_y << " " << cube->rot.m_z << std::endl;
            GameObjectManager::Instance->gameObjects.push_back(cube);
            break;
        }
        case 1: {
            Plane* plane = new Plane(name);
            plane->pos = position;
            plane->scale = scale;
            plane->rot = rotation;
            std::cout << "plane pos: " << plane->pos.m_x << " " << plane->pos.m_y << " " << plane->pos.m_z << std::endl;
            std::cout << "plane scale: " << plane->scale.m_x << " " << plane->scale.m_y << " " << plane->scale.m_z << std::endl;
            std::cout << "plane rot: " << plane->rot.m_x << " " << plane->rot.m_y << " " << plane->rot.m_z << std::endl;
            GameObjectManager::Instance->gameObjects.push_back(plane);
            break;
        }
        case 3: {
            Capsule* capsule = new Capsule(name);
            capsule->pos = position;
            capsule->scale = scale;
            capsule->rot = rotation;
            /*std::cout << "plane pos: " << plane->pos.m_x << " " << plane->pos.m_y << " " << plane->pos.m_z << std::endl;
            std::cout << "plane scale: " << plane->scale.m_x << " " << plane->scale.m_y << " " << plane->scale.m_z << std::endl;
            std::cout << "plane rot: " << plane->rot.m_x << " " << plane->rot.m_y << " " << plane->rot.m_z << std::endl;*/
            GameObjectManager::Instance->gameObjects.push_back(capsule);
            break;
        }
         
    }
}

