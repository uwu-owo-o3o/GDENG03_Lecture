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
	this->width = rc.right - rc.left;
	this->height = rc.bottom - rc.top;
	m_swap_chain->init(this->m_hwnd, width, height);

	SceneCameraHandler::getInstance()->initialize();
	this->cube = new Cube("Cube 1");
}

void AppWindow::onUpdate()
{
	Window::onUpdate();
	InputSystem::get()->update();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5, 0.5, 0.5, 1);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewPortSize(rc.right - rc.left, rc.bottom - rc.top);
	float deltaTime = EngineTime::getDeltaTime();

	SceneCameraHandler::getInstance()->getSceneCamera()->update(deltaTime, width, height);
	cube->update(deltaTime, width, height);
	cube->draw();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();

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

void AppWindow::OnKeyDown(int key)
{
	SceneCameraHandler::getInstance()->getSceneCamera()->moveOnKey(key);
}

void AppWindow::OnKeyUp(int key)
{
	SceneCameraHandler::getInstance()->getSceneCamera()->OnKeyRelease();
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


