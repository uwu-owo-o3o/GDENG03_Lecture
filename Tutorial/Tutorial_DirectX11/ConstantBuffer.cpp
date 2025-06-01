#include "ConstantBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "RenderSystem.h"
#include <exception>

ConstantBuffer::ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* m_system) : m_system(m_system)
{
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	if (FAILED(m_system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		throw std::exception("ConstantBuffer not created successfully.");
	}

}


void ConstantBuffer::update(DeviceContextPtr context, void* buffer)
{
	context->m_device_context->UpdateSubresource(this->m_buffer, NULL, NULL, buffer, NULL, NULL);
}

UINT ConstantBuffer::getSizeVertexList()
{
	return 0;
}

ConstantBuffer::~ConstantBuffer()
{
	if (m_buffer) m_buffer->Release();
}
