#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class PixelShader
{
	public:
		PixelShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* m_system);
		~PixelShader();

	private:
		ID3D11PixelShader* m_ps;
		RenderSystem* m_system = nullptr;
	private:
		friend class RenderSystem;
		friend class GraphicsEngine;
		friend class DeviceContext;
};

