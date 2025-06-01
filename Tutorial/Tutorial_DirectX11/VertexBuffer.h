#pragma once
#include <d3d11.h>
#include "RenderSystem.h"
class DeviceContext;

class VertexBuffer
{
	public:
		VertexBuffer(RenderSystem* m_system);
		bool load(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
		UINT getSizeVertexList();
		bool release();
		~VertexBuffer();

	private:
		UINT m_size_vertex;
		UINT m_size_list;

	private:
		ID3D11Buffer* m_buffer;
		ID3D11InputLayout* m_layout;
		RenderSystem* m_system = nullptr;
	private:
		friend class DeviceContext;
};


