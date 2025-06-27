#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "RenderObject.h"
#include "Camera.h"
#include "InputSystem.h"
#include "EngineTime.h"
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
		void createRenderObjects();

		virtual void OnKeyDown(int key) override;
		virtual void OnKeyUp(int key) override;

		virtual void OnMouseMove(const Point& deltaMousePos) override;

		virtual void OnLeftMouseDown(const Point& deltaMousePos) override;
		virtual void OnLeftMouseUp(const Point& deltaMousePos) override;

		virtual void OnRightMouseDown(const Point& deltaMousePos) override;
		virtual void OnRightMouseUp(const Point& deltaMousePos) override;

	private:
		Camera worldCam;
		SwapChainPtr m_swap_chain;

	private:
		
};
