#pragma once
#include "Resource.h"
#include <d3d11.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh : public Resource
{
	public:
		Mesh(const wchar_t* full_path);
		~Mesh();
		const VertexBufferPtr& getVertexBuffer();
		const IndexBufferPtr& getIndexBuffer();
	private:
		VertexBufferPtr m_vertex_buffer = nullptr;
		IndexBufferPtr m_index_buffer = nullptr;
	private:
		ID3D11Resource* m_texture = nullptr;
		ID3D11ShaderResourceView* m_shader_res_view = nullptr;

	private:
		friend class DeviceContext;
};


