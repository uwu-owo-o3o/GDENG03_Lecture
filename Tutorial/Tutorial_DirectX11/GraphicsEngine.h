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
		bool init();
		bool release();
		RenderSystem* getRenderSystem();

	public:
		static GraphicsEngine* get();

	private:
		RenderSystem* m_render_system = nullptr;
};

