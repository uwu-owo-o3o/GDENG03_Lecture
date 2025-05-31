#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "InputSystem.h"

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

	InputSystem::get()->addListener(this);

	m_swap_chain = GraphicsEngine::get()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	this->sampleObject1.setWindowRef(this->getClientWindowRect());

	this->createRenderObjects();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

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

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::createRenderObjects()
{

	vertex list1[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f),	Vector3D(0, 0 , 0), Vector3D(0, 1 , 0)}, 
		{Vector3D(-0.5f, 0.5f, -0.5f),	Vector3D(1, 1, 0),	 Vector3D(0, 1 , 0)}, 
		{Vector3D(0.5f, 0.5f, -0.5f),	Vector3D(0, 0, 1),	 Vector3D(1, 0 , 0)}, 
		{Vector3D(0.5f, -0.5f, -0.5f),	Vector3D(1, 0, 0),	 Vector3D(0, 0 , 1)},

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f),	Vector3D(0, 0, 0),	 Vector3D(0, 0 , 1)},
		{Vector3D(0.5f, 0.5f, 0.5f),	Vector3D(1, 1, 0),	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D(0, 0, 1),	 Vector3D(0, 0 , 1)},
		{Vector3D(-0.5f, -0.5f, 0.5f),	Vector3D(1, 0, 0),	 Vector3D(0, 0 , 1)},
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

	this->sampleObject1.initialize(list1, ARRAYSIZE(list1), index_list1, ARRAYSIZE(index_list1));

}

void AppWindow::OnKeyDown(int key)
{
	this->sampleObject1.rotateOnKey(key);
}

void AppWindow::OnKeyUp(int key)
{
	this->sampleObject1.OnKeyRelease();
}

void AppWindow::OnMouseMove(const Point& deltaMousePos)
{
	this->sampleObject1.rotateOnMove(deltaMousePos);
}

void AppWindow::OnLeftMouseDown(const Point& deltaMousePos)
{
	this->sampleObject1.scaleOnClick('L');
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
	this->sampleObject1.scaleOnRelease('L');
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
	this->sampleObject1.scaleOnClick('R');
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
	this->sampleObject1.scaleOnRelease('R');
}
