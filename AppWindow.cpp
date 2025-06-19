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

	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	this->worldCam.initialize();
	this->worldCam.setWindowReference(this->getClientWindowRect());

	this->createRenderObjects();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 1, 1, 1, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	this->worldCam.onUpdate();
	this->cube.onUpdate();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

	GraphicsEngine::get()->release();
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
		cube.initialize(list1, ARRAYSIZE(list1), index_list1, ARRAYSIZE(index_list1));
		cube.setWindowRef(this->getClientWindowRect());
		cube.setCameraConstant(&this->worldCam.cc);
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::OnKeyDown(int key)
{
	this->worldCam.moveOnKey(key);
	//this->selectedObjectHelper(key);

	//switch (this->currSelected) {
	//case 1:
	//	this->cube.onKeyDown(key);
	//	break;
	//case 2:
	//	this->cube2.onKeyDown(key);
	//	break;
	//case 3:
	//	this->cube3.onKeyDown(key);
	//	break;
	//case 4:
	//	this->plane.onKeyDown(key);
	//	break;
	//}
}

void AppWindow::OnKeyUp(int key)
{
	this->worldCam.OnKeyRelease();
}

void AppWindow::OnMouseMove(const Point& deltaMousePos)
{
}

void AppWindow::OnLeftMouseDown(const Point& deltaMousePos)
{
	/*switch (this->currSelected) {
	case 1:
		this->cube.onMouseDown('L');
		break;
	case 2:
		this->cube2.onMouseDown('L');
		break;
	case 3:
		this->cube3.onMouseDown('L');
		break;
	case 4:
		this->plane.onMouseDown('L');
		break;
	}*/
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
	/*switch (this->currSelected) {
	case 1:
		this->cube.onMouseDown('R');
		break;
	case 2:
		this->cube2.onMouseDown('R');
		break;
	case 3:
		this->cube3.onMouseDown('R');
		break;
	case 4:
		this->plane.onMouseDown('R');
		break;
	}*/
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
}
