#include "Cube.h"

Cube::Cube(std::string name) : AGameObject(name)
{
	this->create();
}

Cube::Cube(std::string name, Vector3D color) : AGameObject(name)
{
	vertex list[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	color, Vector3D(0, 1 , 0)},
		{Vector3D(-0.5f, 0.5f, -0.5f),	color,	 Vector3D(0, 1 , 0)},
		{Vector3D(0.5f, 0.5f, -0.5f),	color,	 Vector3D(1, 0 , 0)},
		{Vector3D(0.5f, -0.5f, -0.5f),	color,	 Vector3D(0, 0 , 1)},

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	color,	 Vector3D(0, 0 , 1)},
		{Vector3D(0.5f, 0.5f, 0.5f),	color,	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, 0.5f, 0.5f),	color,	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, -0.5f, 0.5f),	color,	 Vector3D(0, 0 , 1)},
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



Cube::~Cube()
{
}

void Cube::create()
{
	vertex list[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(1, 1 , 1), Vector3D(0, 1 , 0)},
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1, 1, 1),	 Vector3D(0, 1 , 0)},
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(1, 1, 1),	 Vector3D(1, 0 , 0)},
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1, 1, 1),	 Vector3D(0, 0 , 1)},

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(1, 1, 1),	 Vector3D(0, 0 , 1)},
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(1, 1, 1),	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(1, 1, 1),	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(1, 1, 1),	 Vector3D(0, 0 , 1)},
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

void Cube::update(float deltaTime, int width, int height)
{
	if (this->hasPhysics) {
		cc.m_world = this->physicsMatrix;
	}
	else {
		Matrix4x4 scale_m;
		scale_m.setIdentity();
		scale_m.setScale(this->scale);

		Matrix4x4 rot_mx;
		rot_mx.setIdentity();
		rot_mx.setRotationX(this->rot.m_x);

		Matrix4x4 rot_my;
		rot_my.setIdentity();
		rot_my.setRotationY(this->rot.m_y);

		Matrix4x4 rot_mz;
		rot_mz.setIdentity();
		rot_mz.setRotationZ(this->rot.m_z);

		Matrix4x4 rotation_m;
		rotation_m = rot_mx * rot_my * rot_mz;

		Matrix4x4 translation_m;
		translation_m.setIdentity();
		translation_m.setTranslation(this->pos);

		Matrix4x4 transform_m = scale_m * rotation_m * translation_m;
		
		cc.m_world = transform_m;
	}
	
	cc.m_view = SceneCameraHandler::getInstance()->getSceneCamera()->cc.m_view;

	cc.m_proj.setPerspectiveFovLH(1.57f, ((float)width / (float)height), 0.1f, 100.0f);

	m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);

}

void Cube::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), m_vb->getSizeVertexList(), 0, 0);

}
