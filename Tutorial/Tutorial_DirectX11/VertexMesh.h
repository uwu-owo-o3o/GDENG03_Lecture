#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
	public:
		VertexMesh() : m_position(), m_texcoord(), m_normal()
		{


		}

		VertexMesh(Vector3D position, Vector2D texcoord, Vector3D normal) : m_position(position), m_texcoord(texcoord), m_normal(normal)
		{


		}

		VertexMesh(const VertexMesh& vertmesh) : m_position(vertmesh.m_position), m_texcoord(vertmesh.m_texcoord), m_normal(vertmesh.m_normal)
		{

		}


		~VertexMesh()
		{

		}

	public:
		Vector3D m_position;
		Vector2D m_texcoord;
		Vector3D m_normal;

};