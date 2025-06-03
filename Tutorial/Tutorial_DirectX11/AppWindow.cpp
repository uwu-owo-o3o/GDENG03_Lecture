#include "AppWindow.h"
#include <Windows.h>
#include <iostream>
#include "InputSystem.h"

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{

	InputSystem::get()->addListener(this);


	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	this->worldCamera.initialize();
	this->sampleObject1.setWindowRef(this->getClientWindowRect());
	this->worldCamera.setWindowReference(this->getClientWindowRect());

	this->createRenderObjects();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0, 0.1f, 0.1f);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	this->worldCamera.onUpdate();
	this->sampleObject1.onUpdate();

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	//this->sampleObject1.onRelease();/*

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

	Vector3D poslist1[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f, -0.5f, -0.5f)}, 
		{Vector3D(-0.5f, 0.5f, -0.5f)}, 
		{Vector3D(0.5f, 0.5f, -0.5f)}, 
		{Vector3D(0.5f, -0.5f, -0.5f)},

		//BACK FACE
		{Vector3D(0.5f, -0.5f, 0.5f)},
		{Vector3D(0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f, -0.5f, 0.5f)},
	};

	Vector2D texcoordlist1[] =
	{
		{Vector2D(0.0f, 0.0f)},
		{Vector2D(0.0f, 1.0f)},
		{Vector2D(1.0f, 0.0f)},
		{Vector2D(1.0f, 1.0f)}
	};

	vertex list1[] =
	{
		{poslist1[0], texcoordlist1[1]},
		{poslist1[1], texcoordlist1[0]},
		{poslist1[2], texcoordlist1[2]},
		{poslist1[3], texcoordlist1[3]},

		{poslist1[4], texcoordlist1[1]},
		{poslist1[5], texcoordlist1[0]},
		{poslist1[6], texcoordlist1[2]},
		{poslist1[7], texcoordlist1[3]},

		{poslist1[1], texcoordlist1[1]},
		{poslist1[6], texcoordlist1[0]},
		{poslist1[5], texcoordlist1[2]},
		{poslist1[2], texcoordlist1[3]},

		{poslist1[7], texcoordlist1[1]},
		{poslist1[0], texcoordlist1[0]},
		{poslist1[3], texcoordlist1[2]},
		{poslist1[4], texcoordlist1[3]},

		{poslist1[3], texcoordlist1[1]},
		{poslist1[2], texcoordlist1[0]},
		{poslist1[5], texcoordlist1[2]},
		{poslist1[4], texcoordlist1[3]},

		{poslist1[7], texcoordlist1[1]},
		{poslist1[6], texcoordlist1[0]},
		{poslist1[1], texcoordlist1[2]},
		{poslist1[0], texcoordlist1[3]},
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
		8,9,10,
		10,11,8,

		//BOTTOM SIDE
		12,13,14,
		14,15,12,

		//RIGHT SIDE
		16,17,18,
		18,19,16,

		//LEFT SIDE
		20,21,22,
		22,23,20

	};

	this->sampleObject1.initialize(list1, ARRAYSIZE(list1), index_list1, ARRAYSIZE(index_list1));

}

void AppWindow::OnKeyDown(int key)
{
	//this->sampleObject1.rotateOnKey(key);
}

void AppWindow::OnKeyUp(int key)
{
	//this->sampleObject1.OnKeyRelease();
}

void AppWindow::OnMouseMove(const Point& deltaMousePos)
{
	//this->sampleObject1.rotateOnMove(deltaMousePos);
}

void AppWindow::OnLeftMouseDown(const Point& deltaMousePos)
{
	//this->sampleObject1.scaleOnClick('L');
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
	//this->sampleObject1.scaleOnRelease('L');
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
	//this->sampleObject1.scaleOnClick('R');
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
	//this->sampleObject1.scaleOnRelease('R');
}
