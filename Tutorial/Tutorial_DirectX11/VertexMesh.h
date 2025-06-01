#pragma once
#include "Vector3D.h"
#include "Vector2D.h"

class VertexMesh
{
	public:
		VertexMesh() : m_position(), m_texcoord()
		{


		}

		VertexMesh(Vector3D position, Vector2D texcoord) : m_position(position), m_texcoord(texcoord)
		{


		}

		VertexMesh(const VertexMesh& vertmesh) : m_position(vertmesh.m_position), m_texcoord(vertmesh.m_texcoord)
		{

		}

		VertexMesh operator *(float num) {
			return VertexMesh(m_position * num, m_texcoord * num);
		}

		VertexMesh operator +(VertexMesh vertmesh) {
			return VertexMesh(m_position + vertmesh.m_position, m_texcoord + vertmesh.m_texcoord);
		}


		~VertexMesh()
		{

		}

	public:
		Vector3D m_position;
		Vector2D m_texcoord;

};