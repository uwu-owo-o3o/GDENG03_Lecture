#include "RenderObject.h"
#include "Texture.h"
#include "Mesh.h"
#include <iostream>

RenderObject::RenderObject()
{
	this->obj_pos = Vector4D(0, 0, 0, 1);
	this->obj_rot = Vector4D(1, 1, 1, 1);
	this->obj_scale = Vector4D(1, 1, 1, 1);
	this->currentColor = Vector3D(1, 1, 1);
	
	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

RenderObject::RenderObject(const wchar_t* filepath)
{
	this->obj_pos = Vector4D(0, 0, 0, 1);
	this->obj_rot = Vector4D(1, 1, 1, 1);
	this->obj_scale = Vector4D(1, 1, 1, 1);
	this->currentColor = Vector3D(1, 1, 1);

	this->createMesh(filepath);
	this->initialize();
	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}


RenderObject::~RenderObject()
{
}

void RenderObject::initialize() {
		
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

}

void RenderObject::onUpdate()
{
	cc.m_cam_pos = camCC->m_cam_pos;
	cc.m_view = camCC->m_view;
	cc.m_proj = camCC->m_proj;
	cc.m_world = camCC->m_world;

	cc.currentColor = this->currentColor;

	cc.m_obj_scale = this->obj_scale;
	cc.m_obj_rot = this->obj_rot;
	cc.m_obj_pos = this->obj_pos;

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time) ? (this->m_new_time - this->m_old_time) / 1000.0f : 0;

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
}

void RenderObject::draw() {

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_vs, m_tex);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_tex);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), m_mesh->getVertexBuffer()->getSizeVertexList(), 0, 0);

}

void RenderObject::onRelease()
{
}

void RenderObject::onKeyDown(int key)
{
	this->translateObj(key);
	this->rotateObj(key);
}

void RenderObject::onKeyRelease()
{
}

void RenderObject::onMouseDown(char c)
{
	this->scaleObj(c);
}

void RenderObject::onMouseUp()
{
}

void RenderObject::onMouseMove(const Point& delta_mouse_pos)
{
}


void RenderObject::translateObj(int key)
{
	if (key == VK_LEFT) 
	{
		this->obj_pos.m_x -= 1.5f * m_delta_time;
	}
	else if (key == VK_RIGHT)
	{
		this->obj_pos.m_x += 1.5f * m_delta_time;
	}
	else if (key == VK_UP)
	{
		this->obj_pos.m_y += 1.5f * m_delta_time;
	}
	else if (key == VK_DOWN)
	{
		this->obj_pos.m_y -= 1.5f * m_delta_time;
	}
	else if (key == VK_OEM_COMMA)
	{
		this->obj_pos.m_z += 1.5f * m_delta_time;
	}
	else if (key == VK_OEM_PERIOD)
	{
		this->obj_pos.m_z -= 1.5f * m_delta_time;
	}
}

void RenderObject::rotateObj(int key)
{
	float rotateMod = 0.5f * m_delta_time;
	if (key == VK_OEM_1)
	{
		this->obj_rot.m_x += rotateMod;
		this->obj_rot.m_y += rotateMod;
		this->obj_rot.m_z += rotateMod;
	}
	else if (key == VK_OEM_7)
	{
		this->obj_rot.m_x -= rotateMod;
		this->obj_rot.m_y -= rotateMod;
		this->obj_rot.m_z -= rotateMod;
	}
}

void RenderObject::scaleObj(char c)
{
	float scaleMod = 0.5f;
	switch (c) {
		case 'L':
			this->obj_scale.m_x += scaleMod;
			this->obj_scale.m_y += scaleMod;
			this->obj_scale.m_z += scaleMod;
			break;
		case 'R':
			this->obj_scale.m_x -= scaleMod;
			this->obj_scale.m_y -= scaleMod;
			this->obj_scale.m_z -= scaleMod;
			break;
	}
}

void RenderObject::setWindowRef(RECT window)
{
	this->windowRef = window;
}

void RenderObject::setCameraConstant(constant* cam_cc)
{
	this->camCC = cam_cc;
}

void RenderObject::createMesh(const wchar_t* filepath)
{
	m_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");
	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(filepath);
}
