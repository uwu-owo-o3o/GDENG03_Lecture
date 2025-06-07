#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
struct vec3 
{
	float x, y, z;
};


struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	//Window::onCreate();
	GraphicsEngine::get()->init();
	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f,	-0.32f, -0.11f, 0.0f,	0, 0 , 0,	0, 1 , 0}, //BOTTOM LEFT
		{-0.5f, 0.5f, 0.0f,		-0.11f, 0.78f, 0.0f,	1, 1, 0,	0, 1 , 0}, //TOP LEFT
		{0.5f, -0.5f, 0.0f,		 0.75f, -0.73f, 0.0f,	0, 0, 1,	1, 0 , 0}, //BOTTOM RIGHT
		{-0.88f, -0.77f, 0.0f,	 1.0f, 1.5f, 0.0f,		1, 1, 1,	0, 0 , 1} //TOP RIGHT
	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(list);

	std::cout << size_list << std::endl;

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);

	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();

	constant cc;
	cc.m_angle = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(constant));


}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 1, 1, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	constant cc;
	m_angle +=  currSpeed * EngineTime::getDeltaTime();

	//if (isIncreasing) {
	//	std::cout << "Entered 1st condition" << std::endl;
	//	this->currSpeed += 1000.0f * EngineTime::getDeltaTime();
	//	m_angle += currSpeed * EngineTime::getDeltaTime();

	//	if (currSpeed >= this->maxSpeed) {
	//		isIncreasing = false;
	//		currSpeed = this->maxSpeed;
	//	}
	//}
	//else {
	//	std::cout << "Entered 2nd condition" << std::endl;
	//	this->currSpeed -= 1000.0f * EngineTime::getDeltaTime();
	//	m_angle -= currSpeed * EngineTime::getDeltaTime();

	//	if (currSpeed <= this->minSpeed) {
	//		isIncreasing = true;
	//		currSpeed = this->minSpeed;
	//	}
	//}

	cc.m_angle = m_angle;
	
	//std::cout << "EngineTime: " << EngineTime::id << std::endl;

	m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_vb->release();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::get()->release();
}
