#pragma once
#include "Matrix4x4.h"
#include "Vector2D.h"
#include "Vector4D.h"
struct vec3
{
	float x, y, z;
};

struct vertex
{
	Vector3D position;
	Vector2D texcoord;
};

__declspec(align(16))
struct constant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;

	Vector4D m_cam_pos;

	Vector3D currentColor;
	int isFlat;

	Matrix4x4 transform_matrix;

};