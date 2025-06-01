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

	m_tex = GraphicsEngine::get()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\brick.png");
	m_mesh = GraphicsEngine::get()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");

	if (m_mesh == nullptr) {
		std::cout << "m_mesh is null" << std::endl;
	}

	m_world_cam.setTranslation(Vector3D(0,0, -2));
	m_ib = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(index_list, size_index_list);
		
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	//m_vb = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->getRenderSystem()->createConstantBuffer(&cc, sizeof(constant));
}

void RenderObject::onUpdate()
{
	this->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_vs, m_tex);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setTexture(m_ps, m_tex);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_mesh->getVertexBuffer());
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_mesh->getIndexBuffer());

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_mesh->getIndexBuffer()->getSizeIndexList(), m_mesh->getVertexBuffer()->getSizeVertexList(), 0, 0);

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time)?(this->m_new_time - this->m_old_time) / 1000.0f:0;
}

void RenderObject::update()
{

	//unsigned long new_time = 0;
	//if (m_old_time)
	//	new_time = ::GetTickCount64() - m_old_time;
	//m_delta_time = new_time / 1000.0f;
	//m_old_time = ::GetTickCount64();
	//m_angle += 1.57f * m_delta_time;
	constant cc;
	cc.m_angle = ::GetTickCount64();

	m_delta_pos += m_delta_time / 10.0f;
	if (m_delta_pos > 1.0f)
		m_delta_pos = 0;

	Matrix4x4 temp;
	m_delta_scale += m_delta_time / 0.55f;

	//cc.m_world.setTranslation(Vector3D::lerp(Vector3D(-2, -2, 0), Vector3D(2, 2, 0), m_delta_pos));
	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f)/2.0f));

	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), m_delta_pos));

	cc.m_world.setScale(Vector3D(m_scale_object, m_scale_object, m_scale_object));
	
	//temp.setIdentity();
	//temp.setRotationZ(0.0f);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationY(m_rot_y);
	//cc.m_world *= temp;

	//temp.setIdentity();
	//temp.setRotationX(m_rot_x);
	//cc.m_world *= temp;

	cc.m_world.setIdentity();

	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(m_rot_x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(m_rot_y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.0005f);

	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.0005f);

	world_cam.setTranslation(new_pos);

	m_world_cam = world_cam;

	world_cam.inverse();

	cc.m_view = world_cam;

	cc.m_proj.setOrthoLH(
		(this->windowRef.right - this->windowRef.left) / 400.0f, 
		(this->windowRef.bottom - this->windowRef.top) / 400.0f, 
		-4.0f, 
		4.0f
	);

	int width = (this->windowRef.right - this->windowRef.left);
	int height = (this->windowRef.bottom - this->windowRef.top);

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width/ (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);


}

void RenderObject::onRelease()
{
}

void RenderObject::rotateOnKey(int key)
{
	if (key == 'W') 
	{
		//m_rot_x += 0.707 * m_delta_time;
		m_forward = 1.0f;
	}
	else if (key == 'S')
	{
		//m_rot_x -= 0.707 * m_delta_time;
		m_forward = -1.0f;
	}
	else if (key == 'A')
	{
		//m_rot_y += 0.707 * m_delta_time;
		m_rightward = -1.0f;
	}
	else if (key == 'D')
	{
		//m_rot_y -= 0.707 * m_delta_time;
		m_rightward = 1.0f;
	}
}

void RenderObject::OnKeyRelease() {
	m_forward = 0.0f;
	m_rightward = 0.0f;
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
