#include "AppWindow.h"
#include <Windows.h>
#include <iostream>


AppWindow::AppWindow()
{
	this->sampleObject1 = RenderObject();
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

	this->sampleObject1.setWindowRef(this->getClientWindowRect());

	this->createRenderObjects();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 1, 1, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	this->sampleObject1.onUpdate();

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

	this->sampleObject1.onRelease();/*
	this->sampleObject2.onRelease();
	this->sampleObject3.onRelease();*/

	GraphicsEngine::get()->release();
}

void AppWindow::createRenderObjects()
{

	vertex list1[] =
	{
		{Vector3D(- 0.5f, -0.3f, 0.0f),	Vector3D(- 0.32f, -0.11f, 0.0f), Vector3D(0, 0 , 0), Vector3D(0, 1 , 0)}, // lower left
		{Vector3D(-0.5f, 0.3f, 0.0f),	Vector3D(-0.11f, 0.78f, 0.0f),	 Vector3D(1, 1, 0),	 Vector3D(0, 1 , 0)}, // top left
		{Vector3D(0.5f, -0.3f, 0.0f),	Vector3D(0.75f, -0.73f, 0.0f),	 Vector3D(0, 0, 1),	 Vector3D(1, 0 , 0)}, // lower right
		{Vector3D(0.5f, 0.3f, 0.0f),	Vector3D(0.88f, 0.77f, 0.0f),	 Vector3D(1, 1, 1),	 Vector3D(0, 0 , 1)} // top right
	};

	this->sampleObject1.initialize(list1, ARRAYSIZE(list1));

}
