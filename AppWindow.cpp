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
	this->teaPot.onUpdate();
	this->armadillo.onUpdate();
	this->bunny.onUpdate();

	this->teaPot.draw();
	this->armadillo.draw();
	this->bunny.draw();
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->teaPot.onRelease();

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
	this->teaPot = RenderObject(L"Assets\\Meshes\\teapot.obj", L"Assets\\Textures\\brick.png", 0);
	this->teaPot.setCameraConstant(&this->worldCamera.cc);
	
	this->armadillo = RenderObject(L"Assets\\Meshes\\armadillo.obj", L"Assets\\Textures\\wood.jpg", 0);
	this->armadillo.setCameraConstant(&this->worldCamera.cc);
	this->armadillo.obj_pos = Vector3D(-3, 0, 0);

	this->bunny = RenderObject(L"Assets\\Meshes\\bunny.obj", L"Assets\\Textures\\wood.jpg", 0);
	this->bunny.setCameraConstant(&this->worldCamera.cc);
	this->bunny.obj_scale = Vector3D(5, 5, 5);
	this->bunny.obj_pos = Vector3D(0.5, 0, 0);

}

void AppWindow::OnKeyDown(int key)
{
	this->worldCamera.moveOnKey(key);
	this->selectedObjectHelper(key);

	switch (this->currSelected) {
		case 1:
			this->teaPot.onKeyDown(key);
			break;
		case 2:
			this->armadillo.onKeyDown(key);
			break;
		case 3:
			this->bunny.onKeyDown(key);
			break;
		case 4:
			break;
	}
}

void AppWindow::OnKeyUp(int key)
{	
	this->worldCamera.OnKeyRelease();
}

void AppWindow::OnMouseMove(const Point& deltaMousePos)
{
}

void AppWindow::OnLeftMouseDown(const Point& deltaMousePos)
{
	switch (this->currSelected) {
		case 1:
			this->teaPot.onMouseDown('L');
			break;
		case 2:
			this->armadillo.onMouseDown('L');
			break;
		case 3:
			this->bunny.onMouseDown('L');
			break;
		case 4:
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
			this->teaPot.onMouseDown('R');
			break;
		case 2:
			this->armadillo.onMouseDown('R');
			break;
		case 3:
			this->bunny.onMouseDown('R');
			break;
		case 4:
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
