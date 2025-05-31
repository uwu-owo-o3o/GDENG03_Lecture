#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "RenderObject.h"

#include "InputListener.h"

class AppWindow : public Window, public InputListener
{
	public:
		AppWindow();
		~AppWindow();

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;
	
	private:
		void createRenderObjects();

	private:
		virtual void OnKeyDown(int key) override;
		virtual void OnKeyUp(int key) override;

		virtual void OnMouseMove(const Point& deltaMousePos) override;

	private:
		SwapChain* m_swap_chain;
		RenderObject sampleObject1;
		//RenderObject sampleObject2;
		//RenderObject sampleObject3;
};

//TRIANGLE
//{ -0.5f, -0.5f, 0.0f, 1, 0, 0 },
//{ 0.0f, 0.5f, 0.0f, 0, 1, 0 },
//{ 0.5f, -0.5f, 0.0f, 0, 0 , 1 }