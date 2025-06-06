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

	this->particle_sys.setConstantRef(&this->worldCamera.cc);
	this->particle_sys.setConstantBufferPtr(this->worldCamera.m_cb);

	this->particle_sys.SpawnParticles();
	//this->createRenderObjects();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0, 0, 0.1f, 0.1f);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	this->particle_sys.updateParticles();
	this->worldCamera.onUpdate();

	this->particle_sys.drawParticles();

	m_swap_chain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();


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

	/*this->sampleObject1.createMesh(L"Assets\\Meshes\\sphere.obj");
	this->sampleObject1.initialize();

	this->sampleObject2.createMesh(L"Assets\\Meshes\\sphere.obj");
	this->sampleObject2.initialize();*/

}

void AppWindow::OnKeyDown(int key)
{
	this->worldCamera.moveOnKey(key);
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
}

void AppWindow::OnLeftMouseUp(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseDown(const Point& deltaMousePos)
{
}

void AppWindow::OnRightMouseUp(const Point& deltaMousePos)
{
}
