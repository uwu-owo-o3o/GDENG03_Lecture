#include "RenderObject.h"

RenderObject::RenderObject()
{
	this->obj_pos = Vector3D(0, 0, 0);
	this->obj_rot = Vector3D(0, 0, 0);
	this->obj_scale = Vector3D(1, 1, 1);

	this->startScale = this->obj_scale;
	this->endScale = Vector3D(10.0f, 2.0f, 1.0f);

	this->startPos = this->obj_pos;
	this->endPos = Vector3D(8, 5.0, 0);

	this->isFlat = 0.0f;
	this->flat_color = Vector3D(1, 1, 1);

	this->reachedEndScale = false;
	this->m_delay_threshold = 1.2f;
	
}

RenderObject::~RenderObject()
{

}

void RenderObject::initialize() {
	vertex list[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1, 0 , 0), Vector3D(0, 1 , 0)},
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(0, 1, 0),	 Vector3D(0, 1 , 0)},
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(0, 0, 1),	 Vector3D(1, 0 , 0)},
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1, 0, 1),	 Vector3D(0, 0 , 1)},

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(1, 0, 0),	 Vector3D(0, 0 , 1)},
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(1, 1, 0),	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0, 0, 1),	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(1, 0, 1),	 Vector3D(0, 0 , 1)},
	};

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,
		2,3,0,

		//BACK SIDE
		4,5,6,
		6,7,4,

		//TOP SIDE
		1,6,5,
		5,2,1,

		//BOTTOM SIDE
		7,0,3,
		3,4,7,

		//RIGHT SIDE
		3,2,5,
		5,4,3,

		//LEFT SIDE
		7,6,1,
		1,0,7

	};
	//vertex* list, UINT size_list, unsigned int* index_list, UINT size_index_list

	UINT size_list = ARRAYSIZE(list);
	UINT size_index_list = ARRAYSIZE(index_list);

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
	cc.m_world = camCC->m_world;
	cc.m_proj = camCC->m_proj;
	cc.m_view = camCC->m_view;

	//cc.isFlat = this->isFlat;
	//cc.color = this->flat_color;
	
	Matrix4x4 scale_m;
	scale_m.setIdentity();
	scale_m.setScale(this->obj_scale);

	Matrix4x4 rot_mx;
	rot_mx.setIdentity();
	rot_mx.setRotationX(this->obj_rot.m_x);

	Matrix4x4 rot_my;
	rot_my.setIdentity();
	rot_my.setRotationY(this->obj_rot.m_y);

	Matrix4x4 rot_mz;
	rot_mz.setIdentity();
	rot_mz.setRotationZ(this->obj_rot.m_z);

	Matrix4x4 rotation_m;
	rotation_m = rot_mx * rot_my * rot_mz;

	Matrix4x4 translation_m;
	translation_m.setIdentity();
	translation_m.setTranslation(this->obj_pos);

	Matrix4x4 transform_m = scale_m * rotation_m * translation_m;

	cc.transform_matrix = transform_m;

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time)?(this->m_new_time - this->m_old_time) / 1000.0f:0;
	//this->m_time_elapsed = this->m_time_elapsed + (this->m_delta_time * 1.0f);

}

void RenderObject::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), m_vb->getSizeVertexList(), 0, 0);

}

void RenderObject::onRelease()
{
	m_vb->release();
	m_ib->release();
	m_cb->release();

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
	float rotateMod = 1.5f * m_delta_time;
	if (key == VK_OEM_1)
	{
		//this->obj_rot.m_x += rotateMod;
		this->obj_rot.m_z += rotateMod;
		//std::cout << "Rotate Z: " << this->obj_rot.m_z << std::endl;
		//this->obj_rot.m_z += rotateMod;
	}
	else if (key == VK_OEM_7)
	{
		//this->obj_rot.m_x -= rotateMod;
		this->obj_rot.m_z -= rotateMod;
		//std::cout << "Rotate Z: " << this->obj_rot.m_z << std::endl;
		//this->obj_rot.m_z -= rotateMod;
	}
}

void RenderObject::scaleObj(char c)
{
	float scaleMod = 0.5f;
	switch (c) {
	case 'L':
		this->obj_scale.m_x += scaleMod;
		this->obj_scale.m_y += scaleMod;
		//this->obj_scale.m_z += scaleMod;
		break;
	case 'R':
		this->obj_scale.m_x -= scaleMod;
		this->obj_scale.m_y -= scaleMod;
		//this->obj_scale.m_z -= scaleMod;
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