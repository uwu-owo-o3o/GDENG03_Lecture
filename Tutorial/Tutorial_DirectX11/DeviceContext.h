#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
	public:
		DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* m_system);
		void clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);

		void setVertexBuffer(const VertexBufferPtr& vertexBuffer);
		void setIndexBuffer(const IndexBufferPtr& indexBuffer);

		void drawTriangleList(UINT vertext_count, UINT start_vertext_index);
		void drawIndexedTriangleList(UINT index_count, UINT vertex_count, UINT start_vertex_index, UINT start_index_loc);
		void drawTriangleStrip(UINT vertext_count, UINT start_vertext_index);

		void setViewPortSize(UINT width, UINT height);

		void setVertexShader(const VertexShaderPtr& vertex_shader);
		void setPixelShader(const PixelShaderPtr& pixel_shader);

		void setTexture(const VertexShaderPtr& vertex_shader, TexturePtr tex);
		void setTexture(const PixelShaderPtr& pixel_shader, TexturePtr tex);

		void setConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer);
		void setConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer);

		~DeviceContext();
		
	private:
		ID3D11DeviceContext* m_device_context;
		RenderSystem* m_system = nullptr;
	private:
		friend class ConstantBuffer;

};


