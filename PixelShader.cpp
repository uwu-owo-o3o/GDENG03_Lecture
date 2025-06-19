#include "PixelShader.h"
#include "GraphicsEngine.h"

PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	if (!SUCCEEDED(GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		throw std::exception("VertexShader not created successfully.");
}

PixelShader::~PixelShader()
{
	m_ps->Release();
	delete this;
}
