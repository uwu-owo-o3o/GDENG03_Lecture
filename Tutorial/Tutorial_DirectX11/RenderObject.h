#pragma once
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Vertex.h"

class RenderObject
{
	public:
		RenderObject();
		~RenderObject();

	public:
		void initialize(vertex* list, UINT size_list);
		void onUpdate();
		void onRelease();

	public:
		unsigned long m_old_time = 0;
		float m_delta_time = 0;
		float m_angle = 0;

	private:
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;
		ConstantBuffer* m_cb;
};

