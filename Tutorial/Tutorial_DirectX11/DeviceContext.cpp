#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):m_device_context(device_context)
{
}

void DeviceContext::clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = {red, green, blue, alpha};
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->m_size_vertex;
	UINT offset = 0;

	m_device_context->IASetVertexBuffers(0, 1, &vertexBuffer->m_buffer, &stride, &offset);

	m_device_context->IASetInputLayout(vertexBuffer->m_layout);	
}

void DeviceContext::drawTriangleList(UINT vertext_count, UINT start_vertext_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertext_count, start_vertext_index);
}

void DeviceContext::setViewPortSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {};
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_device_context->RSSetViewports(1, &vp);
	
}

bool DeviceContext::release()
{
	m_device_context->Release();
	delete this;
	return true;
}

DeviceContext::~DeviceContext()
{
}
