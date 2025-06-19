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
	this->cube2.onUpdate();
	this->cube3.onUpdate();
	this->plane.onUpdate();

	this->cube.draw();
	this->cube2.draw();
	this->cube3.draw();
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

		cube2.initialize();
		cube2.setWindowRef(this->getClientWindowRect());
		cube2.setCameraConstant(&this->worldCam.cc);
		cube2.obj_scale = Vector3D(1, 1, 0.5);
		cube2.obj_pos = Vector3D(1, 1, 2);
		cube2.isFlat = 1;
		cube2.flat_color = Vector3D(0.7, 0.7, 1);

		cube3.initialize();
		cube3.setWindowRef(this->getClientWindowRect());
		cube3.setCameraConstant(&this->worldCam.cc);
		cube3.obj_scale = Vector3D(1, 1, 0.5);
		cube3.obj_pos = Vector3D(-0.5, 1.7, 2);
		cube3.isFlat = 1;
		cube3.flat_color = Vector3D(0.7, 1, 1);

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
	this->selectedObjectHelper(key);

	switch (this->currSelected) {
	case 1:
		this->cube.onKeyDown(key);
		break;
	case 2:
		this->cube2.onKeyDown(key);
		break;
	case 3:
		this->cube3.onKeyDown(key);
		break;
	case 4:
		this->plane.onKeyDown(key);
		break;
	}
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
	switch (this->currSelected) {
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
	}
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
	switch (this->currSelected) {
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
	}
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::selectedObjectHelper(int key)
{
	if (key == '1') {
		this->currSelected = 1;
	}
	else if (key == '2') {
		this->currSelected = 2;
	}
	else if (key == '3') {
		this->currSelected = 3;
	}
	else if (key == '4') {
		this->currSelected = 4;
	}

}