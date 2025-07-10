#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "Cube.h"
#include "Plane.h"
#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "UIManager.h"
#include "vector"

class AppWindow : public Window, public InputListener
{
	public:
		AppWindow();
		~AppWindow();

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

		virtual void onFocus() override;
		virtual void onKillFocus() override;
	
	private:
		virtual void OnKeyDown(int key) override;
		virtual void OnKeyUp(int key) override;

		virtual void OnMouseMove(const Point& deltaMousePos) override;

		virtual void OnLeftMouseDown(const Point& deltaMousePos) override;
		virtual void OnLeftMouseUp(const Point& deltaMousePos) override;

		virtual void OnRightMouseDown(const Point& deltaMousePos) override;
		virtual void OnRightMouseUp(const Point& deltaMousePos) override;

	private:
		int width;
		int height;

	private:
		SwapChainPtr m_swap_chain;
		Cube* cube;
		Plane* plane;

};
