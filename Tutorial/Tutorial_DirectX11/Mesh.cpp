#include "Mesh.h"
#include "VertexMesh.h"
#include "GraphicsEngine.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <iostream>
#include <tiny_obj_loader.h>
#include <filesystem>
#include <exception>
#include "iostream"

Mesh::Mesh(const wchar_t* full_path) : Resource(full_path)
{
	std::cout << "attempt to make mesh" << std::endl;

	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::filesystem::path path = full_path; // full_path is a std::wstring
	std::string utf8Path = path.u8string();

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, utf8Path.c_str());
	//std::cout << "Load success!" << std::endl;

	if (!err.empty() || !res) {
		std::cout << "Mesh Error message not empty! " << err << std::endl;
		throw std::exception("Mesh not created successfully.");
	}

	if (shapes.size() > 1) {
		std::cout << "shapes size is greater than 1!" << err << std::endl;
		throw std::exception("Mesh not created successfully.");
	}

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	//std::cout << "attempt to loop shapes" << std::endl;

	for (size_t s = 0; s < shapes.size(); s++) {

		size_t index_offset = 0;
		list_vertices.reserve(shapes[s].mesh.indices.size());
		list_indices.reserve(shapes[s].mesh.indices.size());

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++) {
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];
				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3 + 0];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				tinyobj::real_t tx = attribs.texcoords[index.texcoord_index * 2 + 0];
				tinyobj::real_t ty = attribs.texcoords[index.texcoord_index * 2 + 1];


				tinyobj::real_t nx = attribs.normals[index.normal_index * 3 + 0];
				tinyobj::real_t ny = attribs.normals[index.normal_index * 3 + 1];
				tinyobj::real_t nz = attribs.normals[index.normal_index * 3 + 2];

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty), Vector3D(nx, ny, nz));
				list_vertices.push_back(vertex);

				list_indices.push_back(index_offset + v);
			}

			index_offset += num_face_verts;	
		}

	}


	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);

	m_vertex_buffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh), (UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);

	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&list_indices[0], (UINT)list_indices.size());
}

Mesh::~Mesh()
{
}

const VertexBufferPtr& Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

const IndexBufferPtr& Mesh::getIndexBuffer()
{
	return m_index_buffer;
}
