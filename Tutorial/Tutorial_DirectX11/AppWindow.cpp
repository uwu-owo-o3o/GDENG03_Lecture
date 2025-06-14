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
	this->cube.onUpdate();
	this->cube2.onUpdate();
	this->cube3.onUpdate();
	this->plane.onUpdate();

	this->cube.draw();
	this->cube2.draw();
	this->cube3.draw();
	this->plane.draw();
	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	this->cube.onRelease();
	this->plane.onRelease();

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
	this->cube = RenderObject(L"Assets\\Meshes\\box.obj", 0);	
	this->cube.setCameraConstant(&this->worldCamera.cc);
	
	this->cube.obj_scale = Vector3D(1, 1.5, 0.5);
	this->cube.obj_pos = Vector3D(0, -0.3, 0);
	this->cube.currentColor = Vector3D(0.5, 0, 0);

	this->cube2 = RenderObject(L"Assets\\Meshes\\box.obj", 0);
	this->cube2.setCameraConstant(&this->worldCamera.cc);
	this->cube2.obj_scale = Vector3D(1, 1, 0.5);
	this->cube2.obj_pos = Vector3D(1, 1, 2);

	this->cube3 = RenderObject(L"Assets\\Meshes\\box.obj", 1);
	this->cube3.setCameraConstant(&this->worldCamera.cc);
	this->cube3.obj_scale = Vector3D(1, 1, 0.5);
	this->cube3.obj_pos = Vector3D(-0.5, 1.7, 2);

	this->plane = RenderObject(L"Assets\\Meshes\\box.obj", 1);
	this->plane.setCameraConstant(&this->worldCamera.cc);

	this->plane.obj_scale = Vector3D(5, 0.01, 5);

}

void AppWindow::OnKeyDown(int key)
{
	this->worldCamera.moveOnKey(key);
	this->cube.onKeyDown(key);
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
	this->cube.onMouseDown('L');
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
	this->cube.onMouseDown('R');
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::selectedObjectHelper(int key) 
{

}
