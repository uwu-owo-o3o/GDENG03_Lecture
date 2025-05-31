#pragma once
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vertex.h"
#include "Matrix4x4.h"
#include "Point.h"

class RenderObject
{
	public:
		RenderObject();
		~RenderObject();

	public:
		void initialize(vertex* list, UINT size_list, unsigned int* index_list, UINT size_index_list);
		void onUpdate();
		void updateQuadPosition();
		void onRelease();

	public:
		void rotateOnKey(int key);
		void rotateOnMove(const Point& delta_mouse_pos);
		void scaleOnClick(char c);
		void scaleOnRelease(char c);

	public:
		void setWindowRef(RECT window);

	public:
		//unsigned long m_old_time = 0;
		float m_old_time = 0;
		float m_new_time = 0;
		float m_delta_time = 0;

		float m_delta_pos = 0;
		float m_delta_scale = 0;

		float m_angle = 0;

		float m_rot_x = 0.0f;
		float m_rot_y = 0.0f;
		float m_rot_z = 0.0f;

		float m_scale_object = 1.0f;

	private:
		RECT windowRef;

	private:
		VertexBuffer* m_vb;		
		ConstantBuffer* m_cb;
		IndexBuffer* m_ib;

		VertexShader* m_vs;
		PixelShader* m_ps;
};

