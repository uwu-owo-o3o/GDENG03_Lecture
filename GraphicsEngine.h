#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
	public:
		GraphicsEngine();
		~GraphicsEngine();

	public:
		RenderSystem* getRenderSystem();
		static GraphicsEngine* get();

		static void create();
		static void release();

	private:

		RenderSystem* m_render_system = nullptr;
		static GraphicsEngine* m_engine;
};

