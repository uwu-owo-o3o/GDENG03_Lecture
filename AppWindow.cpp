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

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5, 0.5, 0.5, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	this->worldCam.onUpdate();
	this->cube.onUpdate();
	this->plane.onUpdate();

	this->cube.draw();
	this->plane.draw();

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
		cube.initialize();
		cube.setWindowRef(this->getClientWindowRect());
		cube.setCameraConstant(&this->worldCam.cc);

		plane.initialize();
		plane.setWindowRef(this->getClientWindowRect());
		plane.setCameraConstant(&this->worldCam.cc);
		plane.isFlat = 1;
		plane.obj_scale = Vector3D(5.0f, 0.1f, 5.0f);

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
