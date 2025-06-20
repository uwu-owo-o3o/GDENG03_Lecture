#include "RenderObject.h"

RenderObject::RenderObject()
{
	this->obj_pos = Vector3D(0, 0, 0);
	this->obj_rot = Vector3D(0, 0, 0);
	this->obj_scale = Vector3D(1, 1, 1);

	this->isFlat = 0.0f;
	this->flat_color = Vector3D(1, 1, 1);
}

RenderObject::~RenderObject()
{

}

void RenderObject::initialize() {
	vertex list[121] ={};

	unsigned int index_list[600] = {};

	this->makeSphere(list, index_list);

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

	cc.isFlat = this->isFlat;
	cc.color = this->flat_color;

	this->bounceSphere();

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

	Matrix4x4 transform_m = translation_m * rotation_m * scale_m;

	cc.transform_matrix = transform_m;

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

	this->m_old_time = this->m_new_time;
	this->m_new_time = ::GetTickCount64();

	this->m_delta_time = (this->m_old_time)?(this->m_new_time - this->m_old_time) / 1000.0f:0;
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

void RenderObject::makeSphere(vertex* list, unsigned int* index_list)
{
	float radius = 1.0f;
	float pi = 3.14;
	Vector3D center = this->obj_pos;

	int stacks = 10;
	int slices = 10;

	int index = 0;

	for (int i = 0; i <= stacks; i++) {
		float stack_angle = (float)i / stacks * pi;
		for (int j = 0; j <= slices; j++) {
			float slice_angle = (float)j / slices * 2 * pi;

			float x = radius * sin(stack_angle) * cos(slice_angle);
			float y = radius * cos(stack_angle);
			float z = radius * sin(stack_angle) * sin(slice_angle);

			Vector3D pos = Vector3D(x, y, z);
			Vector3D color1 = Vector3D(1, 0, 1);
			Vector3D color2 = Vector3D(0, 0, 1);

			list[index] = {pos, color1, color2};
			index++;
		}
	}

	index = 0;
	for (int i = 0; i < stacks; i++) {
		for (int j = 0; j < slices; j++) {
			int top_left = i * (slices + 1) + j;
			int bot_left = top_left + (slices + 1);

			index_list[index + 0] = top_left;
			index_list[index + 1] = bot_left;
			index_list[index + 2] = top_left + 1;

			index_list[index + 3] = bot_left;
			index_list[index + 4] = bot_left + 1;
			index_list[index + 5] = top_left + 1;

			index = index + 6;
		}
	}


}

void RenderObject::bounceSphere()
{
	float radius = 1.0f;
	this->obj_pos.m_x = this->obj_pos.m_x + (this->speed_x * this->m_delta_time);
	this->obj_pos.m_y = this->obj_pos.m_y + (this->speed_y * this->m_delta_time);

	if (this->obj_pos.m_y + radius == this->window_up) {
		this->obj_pos.m_y = this->obj_pos.m_y - 1.0f;
		this->speed_y *= -1.0f;
	}
	else if (this->obj_pos.m_y - radius == this->window_down) {
		this->obj_pos.m_y = this->obj_pos.m_y + 1.0f;
		this->speed_y *= 1.0f;
	}
	else if (this->obj_pos.m_x + radius == this->window_right) {
		this->obj_pos.m_x = this->obj_pos.m_x - 1.0f;
		this->speed_y *= -1.0f;
	}
	else if (this->obj_pos.m_x - radius == this->window_left) {
		this->obj_pos.m_x = this->obj_pos.m_x + 1.0f;
		this->speed_y *= 1.0f;
	}
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
		this->obj_rot.m_y += rotateMod;
		//this->obj_rot.m_z += rotateMod;
	}
	else if (key == VK_OEM_7)
	{
		//this->obj_rot.m_x -= rotateMod;
		this->obj_rot.m_y -= rotateMod;
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