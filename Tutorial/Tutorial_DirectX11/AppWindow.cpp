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

	this->createRenderObjects();
	for (int i = 0; i < 100; i++) {
		this->cubes[i]->setWindowRef(this->getClientWindowRect());
	}
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 1, 1, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	for (int i = 0; i < 100; i++) {
		this->cubes[i]->onUpdate();
	}

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

	for (int i = 0; i < 2; i++) {
		this->cubes[i]->onRelease();
	}

	GraphicsEngine::get()->release();
}

void AppWindow::createRenderObjects()
{
	for (int i = 0; i < 100; i++) {
		vertex list1[] =
		{
			//FRONT FACE
			{Vector3D(-0.5f + i, -0.5f + i, -0.5f + i),	Vector3D(0, 0 , 0), Vector3D(0, 1 , 0)},
			{Vector3D(-0.5f + i, 0.5f + i, -0.5f + i),	Vector3D(1, 1, 0),	 Vector3D(0, 1 , 0)},
			{Vector3D(0.5f + i, 0.5f + i, -0.5f + i),	Vector3D(0, 0, 1),	 Vector3D(1, 0 , 0)},
			{Vector3D(0.5f + i, -0.5f + i, -0.5f + i),	Vector3D(1, 0, 0),	 Vector3D(0, 0 , 1)},

			//BACK FACE
			{Vector3D(0.5f + i, -0.5f + i, 0.5f + i),	Vector3D(0, 0, 0),	 Vector3D(0, 0 , 1)},
			{Vector3D(0.5f + i, 0.5f + i, 0.5f + i),	Vector3D(1, 1, 0),	 Vector3D(0, 0 , 1)},
			{Vector3D(-0.5f + i, 0.5f + i, 0.5f + i),	Vector3D(0, 0, 1),	 Vector3D(0, 0 , 1)},
			{Vector3D(-0.5f + i, -0.5f + i, 0.5f + i),	Vector3D(1, 0, 0),	 Vector3D(0, 0 , 1)},
		};

		unsigned int index_list1[] =
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


		RenderObject* obj = new RenderObject();
		obj->initialize(list1, ARRAYSIZE(list1), index_list1, ARRAYSIZE(index_list1));
		this->cubes.push_back(obj);
		//this->sampleObject1.initialize(list1, ARRAYSIZE(list1), index_list1, ARRAYSIZE(index_list1));

	}
	
}
