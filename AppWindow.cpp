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

}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5, 0.5, 0.5, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);

	this->worldCam.onUpdate();
	this->updateSpheres();
	this->drawSpheres();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

	GraphicsEngine::get()->release();
}

void AppWindow::createSpheres()
{
	RenderObject* spawnedSphere = new RenderObject();
	spawnedSphere->initialize();
	spawnedSphere->setCameraConstant(&this->worldCam.cc);
	spawnedSphere->setWindowRef(this->getClientWindowRect());
	this->spheres.push_back(spawnedSphere);
}

void AppWindow::updateSpheres()
{
	if (this->spheres.size() > 0) 
	{
		for (int i = 0; i < this->spheres.size(); i++) {
			this->spheres[i]->onUpdate();
		}
	}
}

void AppWindow::drawSpheres()
{
	if (this->spheres.size() > 0)
	{
		for (int i = 0; i < this->spheres.size(); i++) {
			this->spheres[i]->draw();
		}
	}
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

	if (key == VK_SPACE && makeSphere) {
		this->createSpheres();
		std::cout << "spheres count: " << spheres.size() << std::endl;
		this->makeSphere = false;
	}
}

void AppWindow::OnKeyUp(int key)
{
	this->worldCam.OnKeyRelease();
	this->makeSphere = true;
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

