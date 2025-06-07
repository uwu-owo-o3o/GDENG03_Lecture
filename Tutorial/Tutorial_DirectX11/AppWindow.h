#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"

class AppWindow : public Window
{
	public:
		AppWindow();
		~AppWindow();
	public:
		unsigned long m_old_time = 0;
		float m_delta_time = 0;
		float m_angle = 0;

	public:
		virtual void onCreate() override;
		virtual void onUpdate() override;
		virtual void onDestroy() override;

	private:
		SwapChain* m_swap_chain;
		VertexBuffer* m_vb;
		VertexShader* m_vs;
		PixelShader* m_ps;
		ConstantBuffer* m_cb;

		float maxSpeed = 20000.0f;
		float minSpeed = 5000.0f;

		float currSpeed = 10000.0f;

		bool isIncreasing = true;
};

//TRIANGLE
//{ -0.5f, -0.5f, 0.0f, 1, 0, 0 },
//{ 0.0f, 0.5f, 0.0f, 0, 1, 0 },
//{ 0.5f, -0.5f, 0.0f, 0, 0 , 1 }