#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class VertexShader
{
	public:
		VertexShader(RenderSystem* m_system);
		void release();
		~VertexShader();

	private:
		bool init(const void* shader_byte_code, size_t byte_code_size);

	private:
		ID3D11VertexShader* m_vs;
		RenderSystem* m_system = nullptr;
	private:
		friend class RenderSystem;
		friend class GraphicsEngine;
		friend class DeviceContext;
};

