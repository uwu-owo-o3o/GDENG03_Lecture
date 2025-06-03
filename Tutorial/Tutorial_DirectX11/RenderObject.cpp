#include "RenderObject.h"
#include "Texture.h"
#include "Mesh.h"
#include <iostream>

RenderObject::RenderObject()
{
}

RenderObject::~RenderObject()
{
}

void RenderObject::initialize(vertex* list, UINT size_list, unsigned int* index_list, UINT size_index_list) {

	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);
		
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"PointLightVertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	//m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PointLightPixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

}

void RenderObject::onUpdate()
{
	this->update();

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time)?(this->m_new_time - this->m_old_time) / 1000.0f:0;
}

void RenderObject::draw() {

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, cb_reference);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, cb_reference);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_vs, m_tex);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_tex);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), m_mesh->getVertexBuffer()->getSizeVertexList(), 0, 0);

}

void RenderObject::update()
{
	constant cc;
	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;
}

void RenderObject::onRelease()
{
}

void RenderObject::rotateOnKey(int key)
{
	if (key == 'W') 
	{
		//m_rot_x += 0.707 * m_delta_time;
		//m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 0.707 * m_delta_time;
		//m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 0.707 * m_delta_time;
		//m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 0.707 * m_delta_time;
		//m_rightward = 1.0f;
	}
	else if (key == 'R')
	{
		//m_rot_y += 0.707 * m_delta_time;
		
	}
}

void RenderObject::OnKeyRelease() {
	//m_forward = 0.0f;
	//m_rightward = 0.0f;
}

void RenderObject::rotateOnMove(const Point& delta_mouse_pos)
{
	m_rot_x -= delta_mouse_pos.m_y * m_delta_time;
	m_rot_y -= delta_mouse_pos.m_x * m_delta_time;
}

void RenderObject::scaleOnClick(char c)
{
	switch (c) {
		case 'L':
			m_scale_object = 0.5f;
			break;
		case 'R':
			m_scale_object = 2.0f;
			break;
	}
}

void RenderObject::scaleOnRelease(char c)
{
	switch (c) {
		case 'L':
		case 'R':
			m_scale_object = 1.0f;
			break;
	}
}

void RenderObject::setWindowRef(RECT window)
{
	this->windowRef = window;
}

void RenderObject::setConstantBufferRef(ConstantBufferPtr cb)
{
	this->cb_reference = cb;
}

void RenderObject::createMesh(const wchar_t* filepath)
{
	m_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\sand.jpg");
	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(filepath);
}
