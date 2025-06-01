#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "IndexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Texture.h"
#include <exception>

DeviceContext::DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* m_system) : m_device_context(device_context), m_system(m_system)
{
}

void DeviceContext::clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] = {red, green, blue, alpha};
	m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
	m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL);
}

void DeviceContext::setVertexBuffer(const VertexBufferPtr& vertexBuffer)
{
	UINT stride = vertexBuffer->m_size_vertex;
	UINT offset = 0;

	m_device_context->IASetVertexBuffers(0, 1, &vertexBuffer->m_buffer, &stride, &offset);

	m_device_context->IASetInputLayout(vertexBuffer->m_layout);	
}

void DeviceContext::setIndexBuffer(const IndexBufferPtr& indexBuffer)
{
	m_device_context->IASetIndexBuffer(indexBuffer->m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::drawTriangleList(UINT vertext_count, UINT start_vertext_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->Draw(vertext_count, start_vertext_index);
}

void DeviceContext::drawIndexedTriangleList(UINT index_count, UINT vertex_count, UINT start_vertex_index, UINT start_index_loc)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_device_context->DrawIndexed(index_count, start_index_loc, start_vertex_index);
}

void DeviceContext::drawTriangleStrip(UINT vertext_count, UINT start_vertext_index)
{
	m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
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

void DeviceContext::setVertexShader(const VertexShaderPtr& vertex_shader)
{
	m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DeviceContext::setPixelShader(const PixelShaderPtr& pixel_shader)
{
	m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setTexture(const VertexShaderPtr& vertex_shader, TexturePtr tex)
{
	m_device_context->VSSetShaderResources(0, 1, &tex->m_shader_res_view);
}

void DeviceContext::setTexture(const PixelShaderPtr& pixel_shader, TexturePtr tex)
{
	m_device_context->PSSetShaderResources(0, 1, &tex->m_shader_res_view);
}

void DeviceContext::setConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer)
{
	m_device_context->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

void DeviceContext::setConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer)
{
	m_device_context->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}

DeviceContext::~DeviceContext()
{
	m_device_context->Release();
}
