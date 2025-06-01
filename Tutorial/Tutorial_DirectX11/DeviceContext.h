#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

class DeviceContext
{
	public:
		DeviceContext(ID3D11DeviceContext* device_context, RenderSystem* m_system);
		void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);

		void setVertexBuffer(VertexBuffer* vertexBuffer);
		void setIndexBuffer(IndexBuffer* indexBuffer);

		void drawTriangleList(UINT vertext_count, UINT start_vertext_index);
		void drawIndexedTriangleList(UINT index_count, UINT vertex_count, UINT start_vertex_index, UINT start_index_loc);
		void drawTriangleStrip(UINT vertext_count, UINT start_vertext_index);

		void setViewPortSize(UINT width, UINT height);

		void setVertexShader(VertexShader* vertex_shader);
		void setPixelShader(PixelShader* pixel_shader);

		void setConstantBuffer(VertexShader* vertex_shader, ConstantBuffer* buffer);
		void setConstantBuffer(PixelShader* pixel_shader, ConstantBuffer* buffer);

		bool release();
		~DeviceContext();
		
	private:
		ID3D11DeviceContext* m_device_context;
		RenderSystem* m_system = nullptr;
	private:
		friend class ConstantBuffer;

};


