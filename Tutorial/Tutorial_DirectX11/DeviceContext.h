#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;

class DeviceContext
{
	public:
		DeviceContext(ID3D11DeviceContext* device_context);
		void clearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
		void setVertexBuffer(VertexBuffer* vertexBuffer);
		void drawTriangleList(UINT vertext_count, UINT start_vertext_index);
		void setViewPortSize(UINT width, UINT height);
		bool release();

		~DeviceContext();
		
	private:
		ID3D11DeviceContext* m_device_context;
};


