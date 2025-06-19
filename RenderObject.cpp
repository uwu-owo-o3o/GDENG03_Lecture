#include "RenderObject.h"

RenderObject::RenderObject()
{
}

RenderObject::~RenderObject()
{
}

void RenderObject::initialize(vertex* list, UINT size_list, unsigned int* index_list, UINT size_index_list) {

	m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer();
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer();
		
	m_ib->load(index_list, size_index_list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));
}

void RenderObject::onUpdate()
{
	this->updateQuadPosition();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), m_vb->getSizeVertexList(), 0, 0);

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time)?(this->m_new_time - this->m_old_time) / 1000.0f:0;
}

void RenderObject::updateQuadPosition()
{
	cc.m_world = camCC->m_world;
	cc.m_proj = camCC->m_proj;
	cc.m_view = camCC->m_view;

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void RenderObject::onRelease()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();
}

void RenderObject::setWindowRef(RECT window)
{
	this->windowRef = window;
}

void RenderObject::setCameraConstant(constant* cam_cc)
{
	this->camCC = cam_cc;
}