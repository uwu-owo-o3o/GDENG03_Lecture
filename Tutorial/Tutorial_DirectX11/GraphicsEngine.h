#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "RenderSystem.h"
#include "Prerequisites.h"

class GraphicsEngine
{
	public:
		GraphicsEngine();
		~GraphicsEngine();
		RenderSystem* getRenderSystem();

	public:
		static GraphicsEngine* get();
		static void create();
		static void release();

	private:
		RenderSystem* m_render_system = nullptr;
		static GraphicsEngine* m_engine;
};

