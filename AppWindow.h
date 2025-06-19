#pragma once
#include "Window.h"
#include "Windows.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "RenderObject.h"
#include "Camera.h"
#include "InputListener.h"
#include "PointLight.h"

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

	private:
		virtual void OnKeyDown(int key) override;
		virtual void OnKeyUp(int key) override;

		virtual void OnMouseMove(const Point& deltaMousePos) override;

		virtual void OnLeftMouseDown(const Point& deltaMousePos) override;
		virtual void OnLeftMouseUp(const Point& deltaMousePos) override;

		virtual void OnRightMouseDown(const Point& deltaMousePos) override;
		virtual void OnRightMouseUp(const Point& deltaMousePos) override;

	private:
		SwapChainPtr m_swap_chain;

	private:
		Camera worldCamera;

	private:
		RenderObject cube;
		RenderObject cube2;
		RenderObject cube3;
		RenderObject plane;

		int currSelected;
	
	private:
		void selectedObjectHelper(int key);
};