#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class PixelShader
{
	public:
		PixelShader(const void* shader_byte_code, size_t byte_code_size);
		~PixelShader();

	private:
		ID3D11PixelShader* m_ps;

	private:
		friend class GraphicsEngine;
		friend class RenderSystem;
		friend class DeviceContext;
};

