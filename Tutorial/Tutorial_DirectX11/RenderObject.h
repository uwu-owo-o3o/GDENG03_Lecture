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
		void update();
		void draw();
		void onRelease();

	public:
		void rotateOnKey(int key);
		void OnKeyRelease();
		void rotateOnMove(const Point& delta_mouse_pos);
		void scaleOnClick(char c);
		void scaleOnRelease(char c);

	public:
		void setWindowRef(RECT window);
		void setConstantBufferRef(ConstantBufferPtr cb);
		void createMesh(const wchar_t* filepath);

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

		float m_scale_object = 10.0f;

	private:
		RECT windowRef;

	private:
		VertexBufferPtr m_vb;	
		ConstantBufferPtr cb_reference;
		IndexBufferPtr m_ib;

		VertexShaderPtr m_vs;
		PixelShaderPtr m_ps;

		TexturePtr m_tex;
		MeshPtr m_mesh;

	private:
		float m_forward = 0.0f;
		float m_rightward = 0.0f;	
};

