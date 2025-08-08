#include "Capsule.h"

Capsule::Capsule(std::string name) : AGameObject(name)
{
	this->create();
}

Capsule::~Capsule()
{
}

void Capsule::create()
{
	vertex list[154] = {};

	unsigned int index_list[660] = {};

	this->MakeCapsule(list, index_list);

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

void Capsule::update(float deltaTime, int width, int height)
{
	if (this->hasPhysics) {
		std::cout << "has physics" << std::endl;
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

void Capsule::draw()
{
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setIndexBuffer(m_ib);

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), m_vb->getSizeVertexList(), 0, 0);

}

void Capsule::MakeCapsule(vertex* list, unsigned int* index_list)
{
    float radius = 1.0f;
    float height = 1.5f;
    float pi = 3.14;
    int slices = 10;
    int stacks = 10; 

    int curr_vertex = 0;
    int curr_index = 0;

    for (int j = 0; j <= slices; j++) {
        float slice_angle = (float)j / slices * 2 * pi;
        float x = radius * cos(slice_angle);
        float z = radius * sin(slice_angle);

        list[curr_vertex++] = { Vector3D(x,  height / 2, z), Vector3D(1,1,1), Vector3D(1,1,1) };
        list[curr_vertex++] = { Vector3D(x, -height / 2, z), Vector3D(1,1,1), Vector3D(1,1,1) };
    }

    for (int j = 0; j < slices; j++) {
        int top_left = j * 2;
        int bottom_left = top_left + 1;
        int top_right = ((j + 1) % (slices)) * 2;
        int bottom_right = top_right + 1;

        index_list[curr_index++] = top_left;
        index_list[curr_index++] = top_right;
        index_list[curr_index++] = bottom_left;

        index_list[curr_index++] = bottom_left;
        index_list[curr_index++] = top_right;
        index_list[curr_index++] = bottom_right;
    }

   
    int top_offset = curr_vertex;
    for (int i = 0; i <= stacks / 2; i++) { 
        float stack_angle = (float)i / (stacks / 2) * (pi / 2); 
        for (int j = 0; j <= slices; j++) {
            float slice_angle = (float)j / slices * 2 * pi;

            float x = radius * sin(stack_angle) * cos(slice_angle);
            float y = radius * cos(stack_angle);
            float z = radius * sin(stack_angle) * sin(slice_angle);

            Vector3D pos = Vector3D(x, y + height / 2, z);
            list[curr_vertex++] = { pos, Vector3D(1,1,1), Vector3D(1,1,1) };
        }
    }

    for (int i = 0; i < stacks / 2; i++) {
        for (int j = 0; j < slices; j++) {
            int top_left = top_offset + i * (slices + 1) + j;
            int bot_left = top_left + (slices + 1);

            index_list[curr_index++] = top_left;
            index_list[curr_index++] = top_left + 1;
            index_list[curr_index++] = bot_left;

            index_list[curr_index++] = bot_left;
            index_list[curr_index++] = top_left + 1;
            index_list[curr_index++] = bot_left + 1;
        }
    }

    int bot_offset = curr_vertex;
    for (int i = 0; i <= stacks / 2; i++) { 
        float stack_angle = (float)i / (stacks / 2) * (pi / 2);
        for (int j = 0; j <= slices; j++) {
            float slice_angle = (float)j / slices * 2 * pi;

            float x = radius * sin(stack_angle) * cos(slice_angle);
            float y = -radius * cos(stack_angle);
            float z = radius * sin(stack_angle) * sin(slice_angle);

            Vector3D pos = Vector3D(x, y - height / 2, z);
            list[curr_vertex++] = { pos, Vector3D(1,1,1), Vector3D(1,1,1) };
        }
    }

    for (int i = 0; i < stacks / 2; i++) {
        for (int j = 0; j < slices; j++) {
            int top_left = bot_offset + i * (slices + 1) + j;
            int bot_left = top_left + (slices + 1);

            index_list[curr_index++] = top_left;
            index_list[curr_index++] = top_left + 1;
            index_list[curr_index++] = bot_left;

            index_list[curr_index++] = bot_left;
            index_list[curr_index++] = top_left + 1;
            index_list[curr_index++] = bot_left + 1;
        }
    }

}